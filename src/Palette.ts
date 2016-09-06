import {Color} from './Color';
import {clamp} from './utils';

export class Palette {
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
