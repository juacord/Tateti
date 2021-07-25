#include<iostream>
#include<iomanip>
#include<cstdio>
using namespace std;

class Ficha
{
private:
	char figura;
public:
	Ficha()
	{
		
	}
	Ficha(char f)
	{
		figura=f;
	}
	
	void setFigura(char f)
	{
		figura=f;
	}
	
	char getFigura()
	{ 
		return figura; 
	}
	
	bool compare(Ficha f)
	{
		return f.getFigura()==figura;
	}
};

class Tablero {
private:
	Ficha mapa[3][3];
public:
	Tablero() 
	{
		for(int i=0; i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				mapa[i][j].setFigura('_');
			}
		}
	}
	char getFichaF(int x,int y)
	{
		return mapa[x][y].getFigura();
	}
	
	void setFichaIn(int x, int y, char c)
	{
		mapa [x][y].setFigura(c); 
	}
	
	void mostrar()
	{
		cout<<"   =============="<<endl;
		cout<<"   = A = B = C = "<<endl;
		
		for(int i=0; i<3;i++)
		{
			cout<<"   --------------"<<endl;
			cout<<" "<<i+1<<" | ";
			for(int j=0;j<3;j++)
			{
				cout<<mapa[i][j].getFigura()<<" | ";
			}
			cout<<endl;
		}
		cout<<"   =============="<<endl;
	}
	
	bool hayFicha(int x,int y)
	{
		return !(mapa[x][y].getFigura()=='_');
	}
	
	bool compararFichas(int x1,int y1,int x2,int y2)
	{
		return mapa[x1][y1].getFigura()==mapa[x2][y2].getFigura();
	}
	
	bool isComplete()
	{
		for(int i=0; i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(!hayFicha(i,j)) return false;
			}
		}
		return true;
	}
};
class Juego {
	
	char jugador1;
	char jugador2;
	bool turno_jugador=true;
	Tablero miTablero;
	
	bool setFichaIn(int x, int y, char c)
	{
		if(!miTablero.hayFicha(x,y))
		{
			miTablero.setFichaIn(x,y,c);
			return true;
		}
		else
		{
			cout<<"[Error] Se intentó poner una ficha en un lugar que ya contiene una ficha. Vuelva a intentarlo"<<endl;
			return false;
		}
	}
	
	void imprimirPantalla(bool opciones=true)
	{
		imprimirCabecera();
		imprimirTablero();
		if(opciones) imprimirOpciones();
		cout<<"Elije una opcion: ";
	}
	
	int nOpcion(int x,int y)
	{
		int temp=-1;
		if(x==0&&y==0) temp=1;
		if(x==0&&y==1) temp=2;
		if(x==0&&y==2) temp=3;
		if(x==1&&y==0) temp=4;
		if(x==1&&y==1) temp=5;
		if(x==1&&y==2) temp=6;
		if(x==2&&y==0) temp=7;
		if(x==2&&y==1) temp=8;
		if(x==2&&y==2) temp=9;
		return temp;
	}
	int getX(int n)
	{
		int temp=-1;
		if(n==1) temp=0;
		if(n==2) temp=0;
		if(n==3) temp=0;
		if(n==4) temp=1;
		if(n==5) temp=1;
		if(n==6) temp=1;
		if(n==7) temp=2;
		if(n==8) temp=2;
		if(n==9) temp=2;
		return temp;
	}
	int getY(int n)
	{
		int temp=-1;
		if(n==1) temp=0;
		if(n==2) temp=1;
		if(n==3) temp=2;
		if(n==4) temp=0;
		if(n==5) temp=1;
		if(n==6) temp=2;
		if(n==7) temp=0;
		if(n==8) temp=1;
		if(n==9) temp=2;
		return temp;
	}
	void imprimirOpciones()
	{
		cout<<endl;
		for(int i=0; i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(!miTablero.hayFicha(i,j))
				{
					char temp;
					switch(j)
					{
					case 0:
						temp='A';
						break;
					case 1:
						temp='B';
						break;
					case 2:
						temp='C';
						break;
					}
					cout<<temp<<i+1<<" presiona "<<nOpcion(i,j)<<endl;
				}
			}
		}
	}
	
	void imprimirTablero()
	{
		miTablero.mostrar();
	}
	
	int getKey()
	{
		int temp=0;
		cin>>temp;
		return temp;
	}
	
	bool checkTateti()
	{
		bool temp=false;
		for(int i=0;i<3;i++)
		{
			if (miTablero.getFichaF(i,0)!= '_' && miTablero.getFichaF(i,0) == miTablero.getFichaF(i,1) && miTablero.getFichaF(i,1) ==miTablero.getFichaF(i,2)) temp=true;
			if(miTablero.getFichaF(0,i) != '_' && miTablero.getFichaF(0,i) == miTablero.getFichaF(1,i) && miTablero.getFichaF(1,i) ==miTablero.getFichaF(2,i))	temp=true;
			if(miTablero.getFichaF(0,0) != '_' && miTablero.getFichaF(0,0) == miTablero.getFichaF(1,1) && miTablero.getFichaF(1,1) ==miTablero.getFichaF(2,2))	temp=true;
			if(miTablero.getFichaF(0,2) != '_' && miTablero.getFichaF(0,2) == miTablero.getFichaF(1,1) && miTablero.getFichaF(1,1) ==miTablero.getFichaF(2,0))	temp=true;
		}
		
		return temp;
	}
	bool checkTermino()
	{
		return miTablero.isComplete();
	}
	
	void imprimirGanador()
	{
		bool temp;
		for(int i=0;i<3;i++)
		{
			if(miTablero.getFichaF(i,0)!= 'X' && miTablero.getFichaF(i,0) == miTablero.getFichaF(i,1) && miTablero.getFichaF(i,1) ==miTablero.getFichaF(i,2))   temp=true;
			if(miTablero.getFichaF(0,i) != 'X' && miTablero.getFichaF(0,i) == miTablero.getFichaF(1,i) && miTablero.getFichaF(1,i) ==miTablero.getFichaF(2,i))	temp=true;
			if(miTablero.getFichaF(0,0) != 'X' && miTablero.getFichaF(0,0) == miTablero.getFichaF(1,1) && miTablero.getFichaF(1,1) ==miTablero.getFichaF(2,2))	temp=true;
			if(miTablero.getFichaF(0,2) != 'X' && miTablero.getFichaF(0,2) == miTablero.getFichaF(1,1) && miTablero.getFichaF(1,1) ==miTablero.getFichaF(2,0))	temp=true;
			
			if(miTablero.getFichaF(i,0)!= 'O' && miTablero.getFichaF(i,0) == miTablero.getFichaF(i,1) && miTablero.getFichaF(i,1) ==miTablero.getFichaF(i,2))   temp=false;
			if(miTablero.getFichaF(0,i) != 'O' && miTablero.getFichaF(0,i) == miTablero.getFichaF(1,i) && miTablero.getFichaF(1,i) ==miTablero.getFichaF(2,i))	temp=false;
			if(miTablero.getFichaF(0,0) != 'O' && miTablero.getFichaF(0,0) == miTablero.getFichaF(1,1) && miTablero.getFichaF(1,1) ==miTablero.getFichaF(2,2))	temp=false;
			if(miTablero.getFichaF(0,2) != 'O' && miTablero.getFichaF(0,2) == miTablero.getFichaF(1,1) && miTablero.getFichaF(1,1) ==miTablero.getFichaF(2,0))	temp=false;
		}
		if(!temp) cout<<"El ganador es el jugador 1!! [X]"<<endl;
		else cout<<"El ganador es el jugador 2!! [O]"<<endl;
	}
	
	void imprimirTerminar(bool) 
	{
		
	}
	
	void imprimirCabecera()
	{
		cout<<"------------------------------------------------------------"<<endl;
		cout<<"Turno del jugador "<<(turno_jugador?"1":"2")<<(turno_jugador?" [X]":" [O]")<<endl;
		cout<<"Elije una posicion para colocar la ficha(presioné el numero posicion escogido y la tecla -enter-): "<<endl;
	}
	
	
public:
	Juego()
	{
		
	}
	void play()
	{
		while(!checkTermino())
		{
			int key=0;
			imprimirPantalla();
			
			key=getKey();
			while(!setFichaIn(getX(key),getY(key),turno_jugador?'X':'O'))
			{
				cout<<"Elije una opcion: ";
				key=getKey();
			}
			turno_jugador=!turno_jugador;
			if(checkTateti())
			{
				imprimirTablero();
				break;
			}
		}
		if(checkTateti())
		{
			imprimirGanador();
		}
		else
		{
			imprimirTablero();
			cout<<endl<<endl<<"No hubo ningún ganador, gracias por jugar."<<endl;
		}
	}
	
	
private:
};

int main(int argc, char *argv[]) {
	
	Juego J;
	J.play();
	system("pause");
	return 0;
}

