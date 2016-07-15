function clamp(n: number, min: number, max: number): number {
    return n < min ? min : (n > max ? max : n);
}

class Color {
    public static BLACK = new Color(0, 0, 0);
    public static WHITE = new Color(1, 1, 1);

    private r: number;
    private g: number;
    private b: number;

    public constructor(r: number, g: number, b: number) {
        this.r = clamp(r, 0, 1);
        this.g = clamp(g, 0, 1);
        this.b = clamp(b, 0, 1);
    }

    public red(): number {
        return this.r;
    }

    public green(): number {
        return this.g;
    }

    public blue(): number {
        return this.b;
    }

    public hex(): string {
        let str = (
            (this.r * 255 << 16) |
            (this.g * 255 << 8) |
            (this.b * 255)
        ).toString(16);

        while (str.length < 6)
            str = '0' + str;

        return str;
    }
}

class Palette {
    private palette: { [key: number]: Color } = {};

    public setColor(t: number, color: Color) {
        this.palette[t] = color;
    }

    public getColor(t: number): Color {
        if (isNaN(t))
            return null;

        t = clamp(t, 0, 1);

        let keys: number[] = Object.keys(this.palette).sort().map(x => +x);
        let count: number = keys.length;

        if (count == 0)
            return null;

        if (count == 1 || t <= keys[0])
            return this.palette[keys[0]];

        if (t >= keys[count - 1])
            return this.palette[keys[count - 1]];

        let prev: number = null;
        let next: number = null;

        for (let i = 0; i < count - 1; ++i) {
            if (keys[i] <= t && t < keys[i + 1]) {
                prev = keys[i];
                next = keys[i + 1];
                break;
            }
        }

        let p: number = (t - prev) / (next - prev);
        let prevc: Color = this.palette[prev];
        let nextc: Color = this.palette[next];

        return new Color(
            (nextc.red()    - prevc.red())      * p + prevc.red(),
            (nextc.green()  - prevc.green())    * p + prevc.green(),
            (nextc.blue()   - prevc.blue())     * p + prevc.blue()
        );
    }
}

class View {
    private _ctx: CanvasRenderingContext2D;
    private _canvas: HTMLCanvasElement;

    private _x: number;
    private _y: number;
    private _scale: number;

    public constructor(canvas: HTMLCanvasElement, x: number, y: number, scale: number) {
        this._ctx = canvas.getContext('2d');
        this._canvas = canvas;
        this._x = x;
        this._y = y;
        this._scale = scale;
    }

    public getCanvas(): HTMLCanvasElement {
        return this._canvas;
    }

    public getX(): number {
        return this._x;
    }

    public getY(): number {
        return this._y;
    }

    public getScale(): number {
        return this._scale;
    }

    public pan(x: number, y: number): void {
        this._x += x / this._scale;
        this._y += y / this._scale;
    }

    public scale(factor: number, x: number, y: number): void {
        let ex = (x - this._canvas.offsetLeft - (this._canvas.width / 2)) / this._scale + this._x;
        let ey = ((y - this._canvas.offsetTop - (this._canvas.height / 2)) / this._scale + this._y);

        this._scale *= factor;

        this._x += ex - ((x - this._canvas.offsetLeft - (this._canvas.width / 2)) / this._scale + this._x);
        this._y += ey - ((y - this._canvas.offsetTop - (this._canvas.height / 2)) / this._scale + this._y);
    }

    public fillRect(x: number, y: number, width: number, height: number, color: Color): void {
        this._ctx.fillStyle = '#' + color.hex();
        this._ctx.fillRect(x, y, x + width, y + height);
    }

    public plot(x: number, y: number, color: Color): void {
        this._ctx.fillStyle = '#' + color.hex();
        this._ctx.fillRect(x, y, x + 1, y + 1);
    }
}

abstract class Fractal {
    private width: number;
    private height: number;

    protected iter: number = 60;
    protected palette: Palette = new Palette();

    public constructor(width: number, height: number) {
        this.width = width;
        this.height = height;
    }

    public getPalette(): Palette {
        return this.palette;
    }

    public getIter(): number {
        return this.iter;
    }

    public render(view: View): number {
        let start = new Date().getTime();

        view.fillRect(0, 0, this.width, this.height, new Color(1, 0, 0));

        let x = view.getX();
        let y = view.getY();
        let scale = view.getScale();

        let hw: number = (this.width / scale) / 2;
        let hh: number = (this.height / scale) / 2;

        for (let i = 0; i < this.width; ++i) {
            for (let j = 0; j < this.height; ++j) {

                let plot = (x_: number, y_: number, color: Color) =>
                    view.plot((x_ - x + hw) * scale, (y_ - y + hh) * scale, color);

                this.compute(i / scale + x - hw, j / scale + y - hh, plot);
            }
        }

        return new Date().getTime() - start;
    }

    protected abstract compute(x0: number, y0: number, plot: (x: number, y: number, color: Color) => void): void;
}

class Mandelbrot extends Fractal {
    protected innerColor: Color = Color.BLACK;

    protected compute(x0: number, y0: number, plot: (x: number, y: number, color: Color) => void): void {
        let x: number = 0;
        let y: number = 0;
        let n: number = 0;

        do {
            let t: number = x * x - y * y + x0;
            y = 2 * x * y + y0;
            x = t;
        } while (++n <= this.iter && x * x + y * y < 1 << 4);

        if (n <= this.iter)
            n += 1 - Math.log(Math.log(x * x + y * y) / 2) / Math.log(2);

        let color = n > this.iter ? this.innerColor : this.palette.getColor(n / this.iter);
        plot(x0, y0, color);
    }
}

interface FractalInfo {
    x: number;
    y: number;
    scale: number;
    iter: number;
    time: number;
}

function setup(fractal: Fractal, view: View, update: (info: FractalInfo) => void) {
    let canvas = view.getCanvas();
    let oldX = null;
    let oldY = null;

    function onUpdate() {
        let time = fractal.render(view);
        update({
            x: view.getX(),
            y: view.getY(),
            scale: view.getScale(),
            iter: fractal.getIter(),
            time: time,
        });
    }

    function onScale(x: number, y: number, button: number): void {
        let scale = null;

        if (button == 0)
            scale = 1.5;
        else if (button == 2)
            scale = 1 / 1.5;

        if (null != scale) {
            view.scale(scale, x, y);
            onUpdate();
        }
    }

    function onPan(x: number, y: number) {
        view.pan(x, y);
        onUpdate();
    }

    canvas.oncontextmenu = (e: PointerEvent) => false;

    canvas.onmousedown = (e: MouseEvent) => {
        oldX = e.pageX;
        oldY = e.pageY;
    };

    canvas.onmouseup = (e: MouseEvent) => {
        if (Math.abs(e.pageX - oldX) <= 2 && Math.abs(e.pageY - oldY) <= 2)
            onScale(e.pageX, e.pageY, e.button);
        else if (null != oldX && null != oldY)
            onPan(oldX - e.pageX, oldY - e.pageY);
    };

    onUpdate();
}
