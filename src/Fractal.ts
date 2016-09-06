import {Color} from './Color';
import {View} from './View';
import {Palette} from './Palette';

export abstract class Fractal {
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
