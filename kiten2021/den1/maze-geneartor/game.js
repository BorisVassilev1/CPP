class Vertex {
	constructor(right, down) {
		if(arguments.length == 0) {
			this.right = true;
			this.down = true;
		} else if(arguments.length == 2) {
			this.right = right;
			this.down = down;
		}
		this.visited = false;
	}
}

let boxSize = 10;
let width = Math.floor(canvas.width / boxSize);
let height = Math.floor(canvas.height / boxSize);

let graph = [];
for(let i = 0; i < width; i ++) {
	graph.push([]);
	for(let j = 0; j < height; j ++) {
		graph[i].push(new Vertex());
	}
}

function is_visited(x, y) {
	return x < 0 || x >= width || y < 0 || y >= height || graph[x][y].visited;
}

function break_wall(x, y, i) {
	switch(i) {
		case 0:
			if(!is_visited(x    , y + 1)) {
				graph[x    ][y    ].down = false;
				dfs(x    , y + 1);
			}
			break;

		case 1: 
			if(!is_visited(x    , y - 1)) {
				graph[x    ][y - 1].down = false;
				dfs(x    , y - 1);
			}
			break;

		case 2:
			if(!is_visited(x + 1, y    )) {
				graph[    x][y    ].right = false;
				dfs(x + 1, y    );
			}
			break;

		case 3:
			if(!is_visited(x - 1, y    )) {
				graph[x - 1][y    ].right = false;
				dfs(x - 1, y    );
			}
			break;
	}
}

function dfs(x, y) {
	graph[x][y].visited = true;
	
	let dirs = [0, 1, 2, 3];

	for(let i = 0; i < 5; i ++) {
		let ind1 = randomInteger(4);
		let ind2 = randomInteger(4);
		
		[dirs[ind1], dirs[ind2]] = [dirs[ind2], dirs[ind1]];
	}

	for(let i = 0; i < 4; i ++) {
		break_wall(x, y, dirs[i]);
	}
}
dfs(randomInteger(width), randomInteger(height));

function update() {
}

function draw() {

	context.strokeRect(0,0, canvas.width, canvas.height);

	context.beginPath();
	for(let i = 0; i < width; i ++) {
		for(let j = 0; j < height; j ++) {
			// x = i * boxSize
			// y = j * boxSize

			//if(graph[i][j].visited) {
			//	context.fillStyle = "yellow";
			//	context.fillRect(i * boxSize, j * boxSize, boxSize, boxSize);
			//}

			if(graph[i][j].right) {
				context.moveTo((i + 1) * boxSize,  j      * boxSize);
				context.lineTo((i + 1) * boxSize, (j + 1) * boxSize);
			}
			if(graph[i][j].down) {
				context.moveTo( i      * boxSize, (j + 1) * boxSize);
				context.lineTo((i + 1) * boxSize, (j + 1) * boxSize);
			}
		}
	}
	context.stroke();
}

function keydown(code) {
}

