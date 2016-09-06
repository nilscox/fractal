import {Color} from './Color';
export class View {
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

    public setX(x: number): void {
        this._x = x;
    }

    public getY(): number {
        return this._y;
    }

    public setY(y: number): void {
        this._y = y;
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
