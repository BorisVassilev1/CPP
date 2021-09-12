let gameOver = false;
let ground_level = 50;
let bird_start_position_x = - canvas.width / 2 + 100;

class Bird {
	
	constructor() {
		this.pos = new Vector2(bird_start_position_x, 0);
		this.vel = new Vector2(0,0);
		this.width = 70; 
		this.height = 40;
		this.rotation = -0.4;
	}

	draw() {
		ctx.save();
		ctx.translate(this.pos.x + this.width / 2, this.pos.y + this.height / 2);
		ctx.rotate(this.rotation);
		ctx.fillStyle = 'green'
		ctx.fillRect( -this.width / 2, -this.height / 2, this.width, this.height);
		ctx.restore();
	}
	
	update() {
		this.vel.y += 0.981 / 3;
		this.pos.add(this.vel);
		this.rotation += 0.01;
		if(this.pos.y < -canvas.height / 2 || this.pos.y > canvas.height / 2 - this.height - ground_level) {
			gameOver = true;
		}
	}

	flap() {
		this.vel.y = -10;
		this.rotation = -0.4;
	}
}

let pipes = [];
let pipe_height = 300;
let pipe_width = 100;
let pipe_distance = 400;
let pipe_count = Math.ceil(canvas.width / pipe_distance);
let pipe_speed = 2;

function get_random_pipe_position() {
	return Math.random() * (canvas.height - 450) + 100 - canvas.height / 2;
}

for(let i = 0; i < pipe_count; i ++) {
	pipes.push(new Vector2(pipe_distance * i, get_random_pipe_position()));
}
let last_pipe = pipes[pipes.length - 1];

let bird = new Bird();

function areColliding(Ax, Ay, Awidth, Aheight, Bx, By, Bwidth, Bheight) {
	if (Bx <= Ax + Awidth) {
		if (Ax <= Bx + Bwidth) {
			if (By <= Ay + Aheight) {
				if (Ay <= By + Bheight) {
					return 1;
				}
			}
		}
	}
	return 0;
};

let score_offset = bird_start_position_x - pipe_width;

function update() {
	if(!gameOver) {
		score_offset += pipe_speed;
		bird.update();

		for(const pipe of pipes) {
			pipe.x -= pipe_speed;
			if(pipe.x < -canvas.width / 2 - pipe_width) {
				pipe.x = last_pipe.x + pipe_distance;
				pipe.y = get_random_pipe_position(); 
				last_pipe = pipe;
			}

			if(areColliding(
				bird.pos.x, bird.pos.y, bird.width, bird.height,
				pipe.x, -canvas.height / 2, pipe_width, canvas.height
			) && !areColliding(
				bird.pos.x, bird.pos.y, bird.width, bird.height,
				pipe.x, pipe.y + bird.height, pipe_width, pipe_height - bird.height * 2
			)) {
				gameOver = true;
			}
		}

	} else {

	}
}

canvas.style.backgroundColor = "lightblue";

function draw() {
	ctx.clearRect(-canvas.width / 2, -canvas.height / 2, canvas.width , canvas.height);

	ctx.fillStyle = 'green';
	ctx.fillRect(-canvas.width / 2, canvas.height / 2 - ground_level, canvas.width, ground_level);

	for(const pipe of pipes) {
		ctx.fillStyle = "blue";
		ctx.fillRect(pipe.x, -canvas.height / 2, pipe_width , canvas.height)
		ctx.fillStyle = "lightblue";
		ctx.fillRect(pipe.x, pipe.y, pipe_width, pipe_height);
	}

	if(gameOver) {
		ctx.fillStyle = "black";
		ctx.font = "50px Arial";
		ctx.fillText("GAME OVER", -200, -200);
	}

	bird.draw();
	
	ctx.fillStyle = "black";
	ctx.font = "50px Arial";
	ctx.fillText("SCORE: " + Math.max(Math.ceil(score_offset / pipe_distance), 0), -canvas.width / 2, -canvas.height / 2 + 50);


	window.requestAnimationFrame(draw);
}


function keyUp(key) {
	if(key == 32 && !gameOver) {
		bird.flap();
	}
}

function keyDown(key) {
}

function mouseDown() {
}

function mouseUp() {
}

window.requestAnimationFrame(draw);

setInterval(update, 10);
