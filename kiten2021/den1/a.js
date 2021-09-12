let a = 2;
let b = "asd";
let c = [1, 2, 3];

let myX, myY;

class Himikalka {
	
	static a = 1;

	constructor(mastilo, duljina, radius) {
		this.mastilo = mastilo;
		this.duljina = duljina;
		this.radius = radius;

		this.currMastilo = mastilo;
		
	}

	
	func(parametri) {
		console.log(this.mastilo);
		return 10;
	}

	static Func(parametri) {
		console.log(this.a);
		return 20;
	}
}

let him = new Himikalka("cherno", 10, 5);
let him2 = new Himikalka("bqlo", 1, 10);
him2.func("asd");
let asd = him.func("alo");
let dfg = Himikalka.Func("balo");

him.asdaw = "asd";

console.log(him);
console.log(him.asdaw);



