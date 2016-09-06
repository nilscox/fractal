import {Color} from './Color';
import {Fractal} from './Fractal';

export class Julia extends Fractal {

  private _x: number;
  private _y: number;

  public constructor(w: number, h: number, x: number, y: number)
  {
    super(w, h);
    this._x = x;
    this._y = y;
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

  protected compute(x0: number, y0: number, plot: (x: number, y: number, color: Color) => void): void {
    let x: number = 0;
    let y: number = 0;
    let n: number = 0;

    do {
      let t: number = x * x - y * y + this._x;
      y = 2 * x * y + this._y;
      x = t;
    } while (++n <= this.iter && x * x + y * y < 1 << 4);

    let color = n > this.iter ? Color.BLACK : this.palette.getColor(n / this.iter);
    plot(x0, y0, color);
  }
}
