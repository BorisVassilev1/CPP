class Position {

	constructor(x, y) {
		this.x = x;
		this.y = y;
	}

	set(x, y) {
		this.x = x;
		this.y = y;
	}

	set(pos) {
		this.set(pos.x, pos.y);
	}

	add(x, y) {
		this.x += x;
		this.y += y;
	}

	add(pos) {
		this.add(pos.x, pos.y);
	}

	sub(x, y) {
		this.add(-x, -y);
	}

	sub(pos) {
		this.sub(pos.x, pos.y);
	}

	mul(a) {
		this.x *= a;
		this.y *= a;
	}
}

function key_code(letter) {
	return letter.charCodeAt(0) - 'a'.charCodeAt(0) + key_a;
}

class Invader {

	static count_x = 8;
	static count_y = 5;
	static width = 50;
	static height = 40;
	static offset_x = Invader.width + 20;
	static offset_y = Invader.height + 20;
	static colors = ["red", "green", "blue", "purple", "brown"];
	static move_direction = 1;
	static speed = 0.5;

	static left_border = 50;
	static right_border = canvas.width - Invader.left_border;

	static check_bounds(invaders) {
		let turn_direction = 0;
		for(let i of invaders) {
			if(i != null) {
				if(i.pos.x < Invader.left_border) {
					turn_direction = 1;
				}
				if(i.pos.x + Invader.width > Invader.right_border) {
					turn_direction = -1;
				}
			}
		}
		if(turn_direction != 0) {
			Invader.move_direction = turn_direction;
		}
	}

	constructor(x, y, color) {
		this.pos = new Position(x, y);
		this.color = color;
	}

	draw() {
		context.fillStyle = this.color;
		context.fillRect(this.pos.x, this.pos.y, Invader.width, Invader.height);
	}

	update() {
		this.pos.x += Invader.move_direction * Invader.speed;
	}
}

class Player {

	static width = 70;
	static height = 40; 
	static color = "green";
	static speed = 5;
	static lives = 3;

	constructor(x, y) {
		this.pos = new Position(x, y);
		this.lives = Player.lives;
	}

	draw() {
		context.fillStyle = Player.color;
		context.fillRect(this.pos.x, this.pos.y, Player.width, Player.height);
	}

	update() {
		if(isKeyPressed[key_code('a')] || isKeyPressed[key_left]) {
			this.pos.x -= Player.speed;
		}
		if(isKeyPressed[key_code('d')] || isKeyPressed[key_right]) {
			this.pos.x += Player.speed;
		}
	}
}

class Bullet {

	static speed = 10;
	static width = 5;
	static height = 30;

	constructor(x, y, direction) {
		this.pos = new Position(x,y);
		this.direction = direction;
	}

	draw() {
		context.fillStyle = 'black'
		context.fillRect(this.pos.x, this.pos.y, Bullet.width, Bullet.height);
	}

	update() {
		this.pos.y -= this.direction * Bullet.speed;
	}

	static check_bounds(bullets) {
		for(let i = 0; i < bullets.length; i ++) {
			const b = bullets[i];
			if(b != null && (b.pos.y < -Bullet.height || b.pos.y > canvas.height)) {
				bullets[i] = null;
			}
		}
	}

	static shoot(x, y, direction, bullets) {
		for(let i = 0; i < bullets.length; i ++) {
			if(bullets[i] == null) {
				bullets[i] = new Bullet(x, y, direction);
				return;
			}
		}
		bullets.push(new Bullet(x, y, direction));
	}
}

let invaders = [];
for(let y = 0; y < Invader.count_y; y ++) {
	for(let x = 0; x < Invader.count_x; x ++) {
		invaders.push(new Invader(x * Invader.offset_x, y * Invader.offset_y, Invader.colors[y]));
	}
}

let player = new Player(canvas.width / 2 - Player.width / 2, canvas.height - Player.height);

let bullets = [];

function check_collisions() {
	for(let i = 0; i < bullets.length; i ++) {
		let bul = bullets[i];
		if(bul != null) {
			for(let j = 0; j < invaders.length; j ++ ) {
				let inv = invaders[j];
				if(inv != null && areColliding(
					inv.pos.x, inv.pos.y, Invader.width, Invader.height, 
					bul.pos.x, bul.pos.y, Bullet.width, Bullet.height)) {
					bullets[i] = null;
					invaders[j] = null;
				}
			}
		}
	}
}


function update() {
	Invader.check_bounds(invaders);
	for(let i of invaders) {
		if(i != null)
			i.update();
	}

	Bullet.check_bounds(bullets);
	for(let b of bullets) {
		if(b != null)
			b.update();
	}

	player.update();

	check_collisions();
}

function draw() {
	for(const i of invaders) {
		if(i != null)
			i.draw();
	}

	for(const b of bullets) {
		if(b != null)
			b.draw();
	}

	player.draw();
}

function keydown(code) {
	if(code == 32) {
		Bullet.shoot(player.pos.x + Player.width / 2, player.pos.y, 1, bullets);
	}
}

