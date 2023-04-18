#include<stdio.h>
#include<graphics.h>
#include<dos.h>
#include<math.h>
int tower[3][10];  
int top[3]; //top of 3 stacks
int from,to;
int diskInAir; //no of disk moved
int left,bottom,up;
void push(int to,int diskno){
    //putting disk on tower
    tower[to-1][++top[to-1]] = diskno;
}
int pop(int from){
    //take topmost disk from tower
    return tower[from-1][top[from-1]--];
}
void drawstill(){
    int i,j,disk;
    cleardevice();
    for( j=1; j<=3; j++){
	//draw tower
	setfillstyle(CLOSE_DOT_FILL,WHITE);
	bar(j*left,up,j*left+5,bottom);
	for(i=0; i<=top[j-1]; i++){ //draw all disk on tower...
	    disk = tower[j-1][i];  
	    setfillstyle(SOLID_FILL,1+disk);
	    bar(j*left-15-disk*5,bottom-(i+1)*10,j*left+5+15+disk*5,bottom-i*10);  //rectbar(left,top,right,bottom)
	}
    }
}
void animator(){
    //to show movement of disk
    int x,y,dif,sign;
    diskInAir = pop(from);
    x = from*left;
    y = bottom-(top[from-1]+1)*10; 
    for(;y>up-20; y-=15){  //taking disk upward from the tower
	drawstill();
	setfillstyle(SOLID_FILL,1+diskInAir); 
	bar(x-15-diskInAir*5,y-10,x+5+15+diskInAir*5,y);
	delay(100);
    }
    y = up-20;
    dif = to*left-x;
    sign = dif/abs(dif);
    for(; abs(x-to*left)>25; x+= sign*15){ //moving disk towards a target tower
	drawstill();
	setfillstyle(SOLID_FILL,1+diskInAir); 
	bar(x-15-diskInAir*5,y-10,x+5+15+diskInAir*5,y);
	delay(100);
    }
    for(; y<bottom-(top[to-1]+1)*10; y+=15){  //placing disk on target tower
	drawstill();
	setfillstyle(SOLID_FILL,1+diskInAir);
	bar(x-15-diskInAir*5,y-10,x+5+15+diskInAir*5,y);
	delay(100);
    }
    push(to,diskInAir);
    drawstill();
}
void movetopN(int n,int a,int b,int c){
    //move top n disk from tower a to c using tower b for swapping
    if(n>=1){
	movetopN(n-1,a,c,b);
	drawstill();
	delay(100);
	from = a;
	to = c;
	animator(); //animating the move
	movetopN(n-1,b,a,c);
    }
}
void main(){
    int i,gd = DETECT,gm,n;
    printf("enter number of disk");
    scanf("%d",&n);
    initgraph(&gd,&gm,"C:\\TURBOC3\\BGI\\");
    for(i=0; i<3; i++){ //setting all tower empty
	top[i] = -1;
    }
    for(i=n; i>0; i--) //putting all disk on tower a
    push(1,i);
    left = getmaxx()/4;
    bottom = getmaxy() - 50;
    up = getmaxy()/3 + 100;
    movetopN(n,1,2,3); //start solving
    delay(4000);
    getch();
}