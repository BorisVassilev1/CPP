class Vector2 {
    constructor(x,y)
    {
        this.x = x;
        this.y = y;
    }
    add(a) {
        this.x += a.x;
        this.y += a.y;
        return this;
    }
    sub(a) {
        this.x -= a.x;
        this.y -= a.y;
        return this;
    }
    mul(a) {
        this.x *= a;
        this.y *= a;
        return this;
    }
    clone() {
        return new Vector2(this.x,this.y);
    }
    length() {
        return Math.sqrt(this.x * this.x + this.y * this.y);
    }
    normalize() {
        let len = this.length()
        this.x /= len;
        this.y /= len;
        return this;
    }
}

class Vector3 {
    constructor(x,y,z)
    {
        this.x = x;
        this.y = y;
        this.z = z;
    }
    add(a) {
        this.x += a.x;
        this.y += a.y;
        this.z += a.z;
        return this;
    }
    sub(a) {
        this.x -= a.x;
        this.y -= a.y;
        this.z -= a.z;
        return this;
    }
    clone() {
        return new Vector3(this.x, this.y, this.z);
    }
    mul(a) {
        this.x *= a;
        this.y *= a;
        this.z *= a;
        return this;
    }
    normalize() {
        let len = this.length();
        this.x /= len;
        this.y /= len;
        this.z /= len;
        return this;
    }
    length() {
        return Math.sqrt(this.x * this.x + this.y * this.y + this.z * this.z);
    }
    
    rotateX(rad) {
        let newz = Math.sin(rad + Math.atan2(this.z,this.y)) * Math.sqrt((this.z) * (this.z) + (this.y) * (this.y));
        let newy = Math.cos(rad + Math.atan2(this.z,this.y)) * Math.sqrt((this.z) * (this.z) + (this.y) * (this.y));
        this.z = newz;
        this.y = newy;
        return this;
    }
    
    rotateY(rad) {
        let newx = Math.sin(rad + Math.atan2(this.x,this.z)) * Math.sqrt((this.x) * (this.x) + (this.z) * (this.z));
        let newz = Math.cos(rad + Math.atan2(this.x,this.z)) * Math.sqrt((this.x) * (this.x) + (this.z) * (this.z));
        this.x = newx;
        this.z = newz;
        return this;
    }
    
    rotateZ(rad) {
        let newx = Math.sin(rad + Math.atan2(this.x,this.y)) * Math.sqrt((this.x) * (this.x) + (this.y) * (this.y));
        let newy = Math.cos(rad + Math.atan2(this.x,this.y)) * Math.sqrt((this.x) * (this.x) + (this.y) * (this.y));
        this.x = newx;
        this.y = newy;
        return this;
    }
}

function singedArea(a,b,c) {
    return a.x*b.y + a.y*c.x + b.x*c.y - b.y*c.x - a.x*c.y - a.y*b.x;
} 

function crossSegments(a, b, c, d){
    let o1 = orientedFace(a, b, c),
        o2 = orientedFace(a, b, d),
        o3 = orientedFace(c, d, a),
        o4 = orientedFace(c, d, b);
    if (o1*o2 < 0 && o3*o4 < 0) return true;
    if (o1 == 0 && (c.x-a.x)*(c.x-b.x) <= 0 && (c.y-a.y)*(c.y-b.y) <= 0) return true;
    if (o2 == 0 && (d.x-a.x)*(d.x-b.x) <= 0 && (d.y-a.y)*(d.y-b.y) <= 0) return true;
    if (o3 == 0 && (a.x-c.x)*(a.x-d.x) <= 0 && (a.y-c.y)*(a.y-d.y) <= 0) return true;
    if (o3 == 0 && (b.x-c.x)*(b.x-d.x) <= 0 && (b.y-c.y)*(b.y-d.y) <= 0) return true;
    return false;
}


class Line {
    constructor(v1,v2) {
        this.v1 = v1;
        this.v2 = v2;
        this.recalculate();
    }
    draw() {
        ctx.beginPath();
        ctx.moveTo(this.v1.x,this.v1.y);
        ctx.lineTo(this.v2.x,this.v2.y);
        ctx.closePath();
        ctx.stroke()
    }
    
    intersection(other) {
        let up = (this.a + other.a) * this.c / this.a - this.c - other.c;
        let down = (this.a + other.a) * (-this.b) / this.a + this.b + other.b;
        let intY = up/down;
        let intX = (-this.b * intY - this.c) / this.a;
        
        if((intX >= this.v1.x && intX <= this.v2.x) || (intX <= this.v1.x && intX >= this.v2.x)) {
            if((intY >= this.v1.y && intY <= this.v2.y) || (intY <= this.v1.y && intY >= this.v2.y)) {
                if((intX >= other.v1.x && intX <= other.v2.x) || (intX <= other.v1.x && intX >= other.v2.x)) {
                    if((intY >= other.v1.y && intY <= other.v2.y) || (intY <= other.v1.y && intY >= other.v2.y)) {
                        
                        return new Vector2(intX, intY);
                    }
                }
            }
        }
        //ctx.fillRect(intX - 5, intY - 5, 10, 10)
        return false;
    }
    
    intersectionBool(other) {
        return crossSegments(this.v1,this.v2, other.v1, other.v2);
    }
    
    recalculate() {
        this.vector = this.v2.clone().sub(this.v1)//.normalize();
        this.a = this.v1.y - this.v2.y;
        this.b = this.v2.x - this.v1.x;
        this.c = this.v1.x * this.v2.y - this.v2.x * this.v1.y;
        this.vector.normalize();
    }
    
    length() {
        return this.v1.clone().sub(this.v2).length();
    }
}

function dijxtra(graph, start,end) {
    let dist = [graph.length];
    let toVisit = [];
    dist[start] = {dist: 0, from: -1};
    toVisit.push(start);
    while(toVisit.length != 0) {
        //console.log(0);
        //finding the "top" of the queue
        let bestInd = 0;
        for(let i = 0; i < toVisit.length; i ++) {
            if(dist[toVisit[i]].dist < dist[toVisit[bestInd]].dist) { 
                bestInd = i;
            }
        }
        //swap the "top" and the last
        let buff = toVisit[toVisit.length - 1];
        toVisit[toVisit.length - 1] = toVisit[bestInd];
        toVisit[bestInd] = buff;
        
        //save and "pop" the last
        let current = toVisit[toVisit.length - 1];
        toVisit.splice(toVisit.length - 1, 1);
        if(current == end) break;
        //go through all the neighbours and push them into the "queue"
        for(let i = 0; i < graph[current].length; i ++) {
            if(dist[graph[current][i].to] == undefined) {
                let distance = dist[current].dist + graph[current][i].dist;
                let to = graph[current][i].to;
                toVisit.push(to);
                dist[to] = {dist: distance,from: current}; 
            }
        }
    }
//    console.log(dist);
    let path = [];
    let current = end;
    while(current != start) {
        current = dist[current].from;
        path.push(current);
    }
//    console.log(path);
    return path;
}
