const canvas = document.getElementById('canvas-id');

const ctx = canvas.getContext('2d');
const refitCanvas = () => {
    canvas.width = window.innerWidth - 10;
    canvas.height = window.innerHeight - 10;
    ctx.fillStyle = "#FF0000";
    ctx.strokeStyle = "#FF0000";
    ctx.translate(canvas.width / 2, canvas.height / 2);
}
refitCanvas();
window.addEventListener('resize', refitCanvas);

document.body.style.backgroundColor = "white";
ctx.fillStyle = "#FF0000";
ctx.strokeStyle = "#FF0000";
let isKeyPressed = [];
let mouseX = 0;
let mouseY = 0;

window.addEventListener('keydown', ev => {keyDown(ev.keyCode); isKeyPressed[ev.keyCode] = true});
window.addEventListener('keyup', ev => {keyUp(ev.keyCode); isKeyPressed[ev.keyCode] = false});
window.addEventListener('mousedown', ev => mouseDown());
window.addEventListener('mouseup', ev => mouseUp());
window.addEventListener('mousemove', ev => {mouseX = ev.x - canvas.width / 2; mouseY = ev.y - canvas.height / 2;});
