import {View} from './View';
import {Fractal} from './Fractal';

interface UpdateInfo {
  time: number;
}

export function setup(fractal: Fractal, view: View, update: (info: UpdateInfo) => void): (() => void) {
    let canvas: HTMLCanvasElement = view.getCanvas();
    let oldX: number = null;
    let oldY: number = null;

    function onUpdate() {
        let time = fractal.render(view);
        update({
            time: time
        });
    }

    function onScale(x: number, y: number, button: number): void {
        let scale: number = null;

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
    return onUpdate.bind(this);
}
