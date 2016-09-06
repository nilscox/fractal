import {Color} from './Color';
import {Fractal} from './Fractal';

export class Mandelbrot extends Fractal {
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
