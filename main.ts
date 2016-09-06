import {Julia} from './src/Julia';
import {Mandelbrot} from './src/Mandelbrot';
import {View} from './src/View';
import {Color} from './src/Color';
import {Palette} from './src/Palette';
import {setup} from './src/setup';

function setDefaultPalette(palette: Palette)
{
  palette.setColor(0.0, new Color(0.0, 0.0, 0.0));
  palette.setColor(0.2, new Color(0.9, 0.5, 0.2));
  palette.setColor(0.4, new Color(0.2, 0.3, 0.9));
  palette.setColor(0.6, new Color(0.8, 0.2, 0.1));
  palette.setColor(0.8, new Color(0.9, 0.1, 0.6));
  palette.setColor(1.0, new Color(1.0, 1.0, 1.0));
}

var canvasses = document.getElementsByTagName('canvas');
var mc = canvasses[0];
var jc = canvasses[1];

let mv: View = new View(mc, -0.5, 0, 100);
let jv: View = new View(jc, -0.5, 0, 100);

let m: Mandelbrot = new Mandelbrot(mc.width, mc.height);
let j: Julia = new Julia(jc.width, jc.height, mv.getX(), mv.getY());

setDefaultPalette(m.getPalette());
setDefaultPalette(j.getPalette());

let mu: () => void = null;
let ju: () => void = null;

mu = setup(m, mv, info => {
    document.getElementById('mvx').innerText = mv.getX().toString();
    document.getElementById('mvy').innerText = mv.getY().toString();
    document.getElementById('mvscale').innerText = mv.getScale().toString();
    document.getElementById('mfiter').innerText = m.getIter().toString();
    document.getElementById('mgtime').innerText = info.time + ' ms';

    if (ju) {
      j.setX(mv.getX());
      j.setY(mv.getY());
      ju();
    }
});

ju = setup(j, jv, info => {
  document.getElementById('jx').innerText = j.getX().toString();
  document.getElementById('jy').innerText = j.getY().toString();
  document.getElementById('jvx').innerText = jv.getX().toString();
  document.getElementById('jvy').innerText = jv.getY().toString();
  document.getElementById('jvscale').innerText = jv.getScale().toString();
  document.getElementById('jfiter').innerText = j.getIter().toString();
  document.getElementById('jgtime').innerText = info.time + ' ms';
});
