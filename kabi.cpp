#include <iostream>
#include <cstdlib>
#include <fstream>
#include <math.h>
#define PI 3.14159265

using namespace std;

float a=1, b=1, c=1, d=1, e=1, f=1;

void CargaAleatorio(){
	
	ifstream in("prob.dat");
	in>>a;
	in>>b;
	in>>c;
	in>>d;
	in>>e;
	in>>f;
	in.close();	

	::a=a;
	::b=b+a;
	::c=c+b;
	::d=d+c;
	::e=e+d;
	::f=f+e;

	cout<<"CargaAleatorio BIEN"<<endl;

}

float FUNCION(int k){ // función que altera el comportamiento de la regeneración según un producto.
    float i=200;
    //return sin(k/i);
    //return 1;
    //return 1-exp(-k/i);
    return (0.5+0.5*cos(2*PI*k/i));
    //if (k<= 1*i){return 0.7;}
    //if (k>= 1*i and k < 2*i){return 0.1;}
    //if (k>= 2*i and k < 4*i){return 0.7;}
    //if (k>= 4*i and k < 8*i){return (1.1+0.5*sin(k/50));}
    //else{return 0.3;}
}

int Aleatorio(){
//Seis factores de peso

float a=::a, b=::b, c=::c, d=::d, e=::e, f=::f, y=0;
int M=0;

y=f*drand48();

if(y<=f){M = 5;}
if(y<=e){M = 4;}
if(y<=d){M = 3;}
if(y<=c){M = 2;}
if(y<=b){M = 1;}
if(y<=a){M = 0;}

return M;
}

//PRUEBA DE ALEATORIO()
int Prueba(){
srand48(time(NULL));
int a=0, b=0, c=0, d=0, e=0, f=0, M=0;

CargaAleatorio();

for(int i=0; i<100000; i++){
switch(Aleatorio()){
	case(0):{a++;
		break;}
	case(1):{b++;
		break;}
	case(2):{c++;
		break;}
	case(3):{d++;
		break;}
	case(4):{e++;
		break;}
	case(5):{f++;
		break;}
}
}
cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<endl;
}


int main(){

//limpiar informacion anterior
system("rm data.d ploter.p video_63.mp4 estats.d");
srand48(time(NULL));
srand(time(NULL));

//definicion de variables varias 
//X->tamaño, mX,mY->posicion inicia, t->iterador, h->generaciones maxima a->nacimientos, b->muertes, c->vegetan, d->total.
//IF->factor de impacto, PAN->maximo valor de medio, RF->factor de regeneración
int X=0, mX=0, mY=0, t=0, h=0, a=0, b=0, c=0, d=0, R=0;
float IF=0, PAN=1, RF=0;

//Pedir datos iniciales
cout<<endl<<"\t-Crecimiento poblacional-"<<endl;
cout<<"Presionar:\n 1 para generar video\n 2 para usar valores por default (solo pide PAN IF y RF) \n cualquier otro número para no generar video e introducir datos\n";
cin>>R;

if(R==0){
	Prueba();
	return 0;}

if(R==2){X=100, mX=50, mY=50, h=1000;}

if(R!=2){
cout<<"Tamaño de grid:"<<endl;
cin>>X;

cout<<"Numero de generaciones:"<<endl;
cin>>h;

cout<<"Ubicación inicial (de 0 a "<<X<<"):"<<endl<<"X: ";
cin>>mX;
cout<<"Y: ";
cin>>mY;
}

cout<<"Valor maximo de PAN"<<endl;
cin>>PAN;

cout<<"Factor de impacto"<<endl;
cin>>IF;

cout<<"Factor de regeneración"<<endl;
cin>>RF;

CargaAleatorio();

//Llenar las matrices

int  moho[X][X], newmoho[X][X];
float pan[X][X];

for(int i=0; i<X; i++){for(int j=0; j<X; j++){
	moho[i][j]=0;
	newmoho[i][j]=0;
	pan[i][j]=PAN;
}}

moho[mX][mY]=1;

//prueba de condiciones iniciales
/*
for(int i=0; i<X; i++){for(int j=0; j<X; j++){	
cout<<i<<" "<<j<<" "<<moho[i][j]<<" "<<newmoho[i][j]<<" "<<pan[i][j]<<endl;
}}
*/
//fin de la prueba

cout<<"Generando datos..."<<endl;

//area de calculo

ofstream estats;
estats.open("estats.d", ios::app);
estats<<"#generación nacen mueren total crecimiento prueba"<<endl;

//k es la generacion. Iteracion para todas as generaciones
for(int k=0;k<=h;k++){	
	
	if(k%50==0){cout<<h-k<<endl;}
	
	a=0;
	b=0;
	c=0;
	d=0;

	ofstream plt("ploter.plt");
	ofstream data;
	data.open("data.dat", ios::app);

	//Iteracion para todos los cuadros del grid
	for(int i=0; i<X; i++){for(int j=0; j<X; j++){	
	
		//Si no hay suficiente que comer el moho muere
		if(pan[i][j]<IF && moho[i][j]==1)
			{moho[i][j]=0;
			b++;
			}

		//si hay moho y hay pan, que coma pan	
		if(moho[i][j]==1 && pan[i][j]>=IF){pan[i][j]=pan[i][j]-IF;}

		//0 arriba, 1 abajo, 2 derecha, 3 izquierda, 4 muere, 5 permanece
		t=Aleatorio(); 
		if(moho[i][j]==1){
			if(t==0 && moho[i+1][j]==0 && newmoho[i+1][j]==0 && pan[i+1][j]>IF && i+1>0 && i<X){newmoho[i+1][j]=1;
			a++;}else{;}
			if(t==1 && moho[i-1][j]==0 && newmoho[i-1][j]==0 && pan[i-1][j]>IF && i-1>0 && i<X){newmoho[i-1][j]=1;
			a++;}else{;}
			if(t==2 && moho[i][j+1]==0 && newmoho[i][j+1]==0 && pan[i][j+1]>IF && j>0 && j+1<X){newmoho[i][j+1]=1;
			a++;}else{;}
			if(t==3 && moho[i][j-1]==0 && newmoho[i][j-1]==0 && pan[i][j-1]>IF && j>0 && j-1<X){newmoho[i][j-1]=1;
			a++;}else{;}
			newmoho[i][j]=1;
			if(t==4 && moho[i][j]==1 && pan[i][j]>IF){newmoho[i][j]=0;
			b++;}
			if(t==5){;}
			}

		//Si el pan puede crecer que lo haga
		if(pan[i][j]<PAN){pan[i][j]=pan[i][j]+RF*FUNCION(k);}
	
		//Si se genera video la informacion va a data.d, si no solo suma 	
		if(R!=1){if(moho[i][j]==1){d++;}}
		if(R==1){
			if(moho[i][j]==1){
				data<<k<<" "<<i<<" "<<j<<" "<<moho[i][j]<<" "<<pan[i][j]<<endl;
				d++;
				}
			}
	}}

	//si todos han muerto que avice
	if(d==0){
		cout<<"Han muerto todos en la generación "<<k<<endl;
		
		//system("rm data.d ploter.p");
		if(k!=0){system("gnuplot resumen.plt -persist");}
		return 1;
		}

	//Si se genera video se manda a llamar a gnuplot para generar la imagen, apartir de data.d, por medio de ploter.p
	if(R==1){
		plt<<"set style line 1 lt 2 lw 1 pt 7 ps 1;\n set size square;"<<"\n a="<<k<<endl;
		plt<<"set term png size 600,600;if (a<=9) b='img000'.a.'.png'; else if(a>=10 && a<100) b='img00'.a.'.png'; 			else if(a>=100 && a<1000) b='img0'.a.'.png'; else if(a>=1000) b='img'.a.'.png';"<<endl<<" set output b;;\nset 			view map; \n splot [0:"<<X<<"][0:"<<X<<"] 'data.d' u 2:3:5 not ls 1, 'data.d'u 2:3:4 not w dots ; \n replot; 			\n exit;";

		plt.close();
		data.close();

		system("gnuplot ploter.plt");
		system("rm data.dat");
		}

//Todas las estadisticas de nacimientos, muertes, latencias y totales se guarda en estats.d
	estats<<k<<" "<<a<<" "<<b<<" "<<" "<<d<<" "<<a-b<<" "<<log(d)<<" "<<endl;

//se actualizan los valores de moho a los nuevos calculados y limpia new moho
	for(int i=0; i<X; i++){for(int j=0; j<X; j++){
		moho[i][j]=newmoho[i][j];
		newmoho[i][j]=0;
		}}
}

//fin de calculo

//cierra estats.d
estats.close();

//si se genera video aqui lo hace, borra las imagenes
if(R==1){
	cout<<"\t¡Listo!\n";
	cout<<"Generando video...";

	//system("ffmpeg -r 12 -i img%04d.png video_63.mp4");
    system("ffmpeg -r 12 -i img%04d.png -c:v libx264 -r 30 -pix_fmt yuv420p out.mp4");

	cout<<"\t¡Listo!\n";
	cout<<"Borrando imagenes...";

	system("rm img????.png");
	}

//Borra la informacion indeseada
system("rm data.dat ploter.plt");

// Muestra la evolución como un resumen
system("gnuplot resumen.plt -persist");

//Termina el programa
cout<<"\t¡Listo!"<<endl<<"\t-Fin del programa-"<<endl;

return 0;
}


