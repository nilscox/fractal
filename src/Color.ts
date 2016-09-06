import {clamp} from './utils';

export class Color {
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
