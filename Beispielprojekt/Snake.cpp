#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <stdlib.h>
#include<list>
#include <iostream>

using namespace std;



class Schlangenstueck {				//class Schlangenstuecke
public:

	int x;
	int y;
	Gosu::Color farbe = Gosu::Color::GREEN;
	int schrittweite = 10;

	int geschwindigkeit = 30;
	int richtung = 0;

	Schlangenstueck() {

		
		x = (rand() % ((800 / schrittweite) - 1) * schrittweite);
		y = (rand() % ((600 / schrittweite) - 1) * schrittweite);
		int farbwahl = (rand() % 3);

		if(farbwahl == 0){

			farbe = Gosu::Color::GREEN;

		}
		else if (farbwahl == 1) {

			farbe = Gosu::Color::BLUE;

		}
		else if (farbwahl == 2) {

			farbe = Gosu::Color::YELLOW;
		}
	}

	Schlangenstueck(int x, int y, Gosu::Color farbe) {
		this->x = x;
		this->y = y;
		this->farbe = farbe;
	}

	Schlangenstueck(const Schlangenstueck& copy) {
		*this = copy;
	}

};

class Schlange {				//class Schlange 
public:
	int spielfeld_x = 800;
	int spielfeld_y = 600;
	int schrittweite = 10;

	int x = 400;					//Schlangenstartwert
	int y = 300;

	Gosu::Color farbe = Gosu::Color::GREEN;
	//int leben = 3;				//durch Sonderteile Leben dazugewinnen? Oder Punkte abziehen wenn man ein Leben verliert?

	int geschwindigkeit = 10;	//Geschwindigkeitsstartwert
	int richtung = 0;

	std::list<Schlangenstueck> koerper = {Schlangenstueck(410, 300, Gosu::Color::GREEN), Schlangenstueck(420,300, Gosu::Color::GREEN), Schlangenstueck(430,300, Gosu::Color::BLUE)};

	bool schlangenbewegung() {			//Bewegungsausf�hrung in Abh�ngigkeit der Richtung

		/*auto itr1 = map.begin();
		for (auto itr2 = itr1++; itr1 != map.end(); itr2 = itr1++)
		{
			// do stuff
		}*/


		auto vorderer_teil = koerper.rbegin();					//Schlangenst�cke hinterherlaufen lassen
		if (richtung != 0) {
			for (auto hinterer_teil = vorderer_teil++; vorderer_teil != koerper.rend(); hinterer_teil = vorderer_teil++)
			{
				printf("%d ", vorderer_teil->x);		//nur zum Testen
				hinterer_teil->x = vorderer_teil->x;
				hinterer_teil->y = vorderer_teil->y;

			}

			printf("\n"); //nur zum Testen
			koerper.front().x = x;
			koerper.front().y = y;
		}

		if (richtung == 1) {

			x = x - schrittweite;
		}
		else if (richtung == 2) {

			x = x + schrittweite;
		}
		else if (richtung == 3) {

			y = y + schrittweite;
		}
		else if (richtung == 4) {

			y = y - schrittweite;
		}
		ueberprueferaender();
		return schlange_getroffen(x, y);

	}

	bool aufsammeln(Schlangenstueck schlangenstueck) {
		if (schlangenstueck.x == koerper.back().x && schlangenstueck.y == koerper.back().y) {
			koerper.push_back(schlangenstueck);
			return true;
		}
		return false;
	}


	void gehlinks() {				//Richtungsfestlegung
		if (richtung != 2) {

			richtung = 1;

		}

	}
	void gehrechts() {
		if (richtung != 1) {

			richtung = 2;
		}
	}

	void gehnachunten() {
		if (richtung != 4) {

			richtung = 3;
		}

	}

	void gehnachoben() {
		if (richtung != 3) {

			richtung = 4;
		}

	}
	void pause() {
		richtung = 0;
	}

	void ueberprueferaender() {			//Randbetrachtung
		if (x == spielfeld_x) {
			x = 0;
		}
		else if (x == - schrittweite) {
			x = spielfeld_x - schrittweite;
		}
		else if (y == spielfeld_y) {
			y = 0;
		}
		else if (y == - schrittweite) {
			y = spielfeld_y - schrittweite;
		}

	}

	bool schlange_getroffen(int x, int y) {
		for (auto it = koerper.begin(); it != koerper.end(); it++) {

			if (it->x == x && it->y == y) {
				return true;
			}


		}
		return false;

	}

	//Geschwindigkeitsanpassungsfunktion 
	//printf("%d ", geschwindigkeit); 

};




		



//Hier binde ich alle Audio Dateien und Bilder ein die wir verwenden

Gosu::Image hintergrundbild("Hintergrundbild3.png");
Gosu::Image musikleise("musikleise.png");
Gosu::Image musiklaut("musiklaut.png");
Gosu::Image musikaus("musikaus.png");
Gosu::Image wall("brickwall.jpg");
Gosu::Image v12("v12.png");
Gosu::Image v34("v34.png");
Gosu::Image v56("v56.png");
Gosu::Image v78("v78.png");
Gosu::Image v910("v910.png");
Gosu::Image menu("menu.png");
Gosu::Image gameover_screen("gameoverscreen.png");

Gosu::Song musik("Hintergrundmusik.mp3");
Gosu::Sample apfel("Apfel essen.mp3");

Gosu::Font bla(10);


class GameWindow : public Gosu::Window
{
public:

	GameWindow()
		: Window(1000, 600)
	{
		set_caption("Snake");
	}
	
	//Initialisierung Werte

	Schlange schlange = Schlange();
	Schlangenstueck schlangenstueck = Schlangenstueck();
	

	int x = 0;
	int y = 0;
	/*int x_1 = 0;
	int y_1 = 10;
	int x_2 = 0;
	int y_2 = 20;*/
	int updatezaehler = 0;
	int geschwindigkeit = 30;							//Ladebalken der Geschwindigkeit stufenweise anzeigt?
	int richtung = 0;
	int neue_richtung = 0;
	int anzahlsteine = 0;
	int stein_x = 60;
	int stein_y = 70;
	int ergaenzung_x = 0;
	int ergaenzung_y = 0;
	Gosu::Color ergaenzung_farbe = Gosu::Color::GREEN;
	int schrittweite = 10;
	
	int anzahl_essen = 0;								//ausgeben
	int anzahl_hindernisse = 0;							//ausgeben
	int hinderniss_x;
	int hinderniss_y;

	bool gameover = false;								//f�r die Sterbefunktion
	int punktestand = 0;
	
	

	// Wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{



		//Bilder
		hintergrundbild.draw(240, 150, 0, 1, 1);									//Sarah: Einbindung Hintergrundbild. Bild ist vielleicht nicht das beste xD
		wall.draw(800, 0, 3, 0.4, 0.6, Gosu::Color::WHITE, Gosu::BlendMode::BM_INTERPOLATE);
		menu.draw(830, 0, 3, 0.5, 0.5);
		
		//Men�leiste/Text
		bla.draw_text("Score: ", 810, 110, 3, 3, 3,Gosu::Color::GREEN, Gosu::BlendMode::BM_ADD);
		bla.draw_text("Speed: ", 810, 200, 3, 3, 3, Gosu::Color::GREEN, Gosu::BlendMode::BM_ADD);
		bla.draw_text("Volume:", 810, 300, 3, 3, 3, Gosu::Color::GREEN, Gosu::BlendMode::BM_ADD);

		//Men�leiste: Icons

		musikaus.draw(800, 320, 3,0.3,0.3);
		musikleise.draw(850, 320, 3,0.3,0.3);
		musiklaut.draw(900, 320,3, 0.3 ,0.3);

		if ((8 < schlange.geschwindigkeit) && (schlange.geschwindigkeit <= 10))
		{
			v910.draw(810, 220, 3, 0.5, 0.5);
		};
		if ((6 < schlange.geschwindigkeit) && (schlange.geschwindigkeit <= 8))
		{
			v78.draw(810, 220, 4, 0.5, 0.5);
		};
		if ((4 < schlange.geschwindigkeit) && (schlange.geschwindigkeit <= 6))
		{
			v56.draw(810, 220, 5, 0.5, 0.5);
		};
		if ((2 < schlange.geschwindigkeit) && (schlange.geschwindigkeit <= 4))
		{
			v34.draw(810, 220, 6, 0.5, 0.5);
		};
		if ((1 <= schlange.geschwindigkeit) && (schlange.geschwindigkeit <= 2))
		{
			v12.draw(810, 220, 7, 0.5, 0.5);
		};


		graphics().draw_quad(				//Schlangenkopf (class)
			schlange.x, schlange.y, schlange.farbe,
			schlange.x, schlange.y + schlange.schrittweite, schlange.farbe,
			schlange.x + schlange.schrittweite, schlange.y, schlange.farbe,
			schlange.x + schlange.schrittweite, schlange.y + schlange.schrittweite, schlange.farbe,
			0.0
		);



		for (auto it = schlange.koerper.begin(); it != schlange.koerper.end(); it++) {

			graphics().draw_quad(				//Schlangenstueck vom Koerper (class)
				it->x, it->y, it->farbe,
				it->x, it->y + schlange.schrittweite, it->farbe,
				it->x + schlange.schrittweite, it->y, it->farbe,
				it->x + schlange.schrittweite, it->y + schlange.schrittweite, it->farbe,
				0.0
			);
		}
	
		


		graphics().draw_quad(				//Schlangenstueck zum Essen (class)
			schlangenstueck.x, schlangenstueck.y, schlangenstueck.farbe,
			schlangenstueck.x, schlangenstueck.y + schlangenstueck.schrittweite, schlangenstueck.farbe,
			schlangenstueck.x + schlangenstueck.schrittweite, schlangenstueck.y, schlangenstueck.farbe,
			schlangenstueck.x + schlangenstueck.schrittweite, schlangenstueck.y + schlangenstueck.schrittweite, schlangenstueck.farbe,
			0.0 
		);

		graphics().draw_quad(			//F�r Hindernis sp�ter
			hinderniss_x, hinderniss_y, Gosu::Color::RED,
			hinderniss_x, hinderniss_y + schrittweite, Gosu::Color::RED,
			hinderniss_x + schrittweite, hinderniss_y, Gosu::Color::RED,
			hinderniss_x + schrittweite, hinderniss_y + schrittweite, Gosu::Color::RED, 0.0
		);

		if (gameover) {
			gameover_screen.draw(0, 0, 2, 1.18, 1.18);
		}



		
		/*graphics().draw_quad(				//Schlangenkopf
			x, y, Gosu::Color::BLUE,
			x, y + schrittweite, Gosu::Color::BLUE,
			x + schrittweite, y, Gosu::Color::BLUE,
			x + schrittweite, y + schrittweite, Gosu::Color::BLUE,
			0.0
		);



		//nur zum Testen der Richtung Schlangengroessenerweiterung 
		graphics().draw_quad(				//Schlange+1
			x_1, y_1, Gosu::Color::BLUE,
			x_1, y_1 + schrittweite, Gosu::Color::BLUE,
			x_1 + schrittweite, y_1, Gosu::Color::BLUE,
			x_1 + schrittweite, y_1 + schrittweite, Gosu::Color::BLUE,
			0.0
		);
		graphics().draw_quad(				//Schlange+2
			x_2, y_2, Gosu::Color::BLUE,
			x_2, y_2 + schrittweite, Gosu::Color::BLUE,
			x_2 + schrittweite, y_2, Gosu::Color::BLUE,
			x_2 + schrittweite, y_2 + schrittweite, Gosu::Color::BLUE,
			0.0
		);*/




		/*graphics().draw_quad(				//Essensstein (nur fuer alte Schlange, bei der neuen sind es Schlangenst�cke)					
			stein_x, stein_y, Gosu::Color::YELLOW,
			stein_x, stein_y + 5, Gosu::Color::YELLOW,
			stein_x + 5, stein_y, Gosu::Color::YELLOW,
			stein_x + 5, stein_y + 5, Gosu::Color::YELLOW,
			0.0
		);*/

		/*graphics().draw_quad(				//Menuefeld
			801, 0, Gosu::Color::GRAY,
			801, 601, Gosu::Color::GRAY,
			1000, 0, Gosu::Color::GRAY,
			1000, 601, Gosu::Color::GRAY,
			0.0,Gosu::BlendMode::BM_INTERPOLATE					//ersetzt durch ein Bild
		);*/
			
		


	}
	
	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		musik.play(true);		//Hintergrundmusik in Endlosschleife
		//
		// 
		// 
		punktestand = (schlange.koerper.size()) * 5;
		//printf("%d ", punktestand);  //d richtig???? ... nicht hier aufrufen.. sonst 60 mal ???
		// 
		// 
		//Pfeilzuordnungen + Pausenfunktion + wenn man in die Schlange laufen will wird die Richtung beibehalten
		if (input().down(Gosu::KB_LEFT)) {
			//x = x - schrittweite;
			
			neue_richtung = 1;
			/*if (richtung == 2) {
				richtung = 2;

			}
			else {
				richtung = 1;
			}*/
			
		}
		else if (input().down(Gosu::KB_RIGHT)) {
			neue_richtung = 2;
			//x = x + schrittweite;
			/*if (richtung == 1) {
				richtung = 1;
			}
			else {
				richtung = 2;
			}*/
			
		}
		else if (input().down(Gosu::KB_DOWN)) {
			neue_richtung = 3;
			/*if (richtung == 4) {
				richtung = 4;
			}
			else {
				richtung = 3;

			}*/
			
		}
		else if (input().down(Gosu::KB_UP)) {
			neue_richtung = 4;
			/*if (richtung == 3) {
				richtung = 3;
			}
			else {
				richtung = 4;
			}*/

		}
		else if (input().down(Gosu::KB_SPACE)) {

			if (gameover) {
				schlange = Schlange();
				gameover = false;
			}
			else {
			schlange.pause();
			neue_richtung = 0; //ge�ndert von richtung
			}
		}

		if (gameover) {
					return;
				}

		
		/*//Randbetrachtung
		if (x == 800) {
			x = 0;
		}
		else if (x == -schrittweite) {
			x = 800 - schrittweite;
		}
		else if (y == 600) {
			y = 0;
		}
		else if (y == -schrittweite) {
			y = 600 - schrittweite;
		}
		*/
		

		updatezaehler = updatezaehler + 1;	//Zaehlt wie oft update aufgerufen wird, fuer Geschwindigkeitsanpassung(FUER BEIDE)
		//Was passiert bei den Verschieden Richtungen (class)
		if (updatezaehler % schlange.geschwindigkeit == 0) {
			if (neue_richtung == 1) {
				schlange.gehlinks();
			}
			else if(neue_richtung == 2) {
				schlange.gehrechts();

			}
			else if (neue_richtung == 3) {
				schlange.gehnachunten();
			}
			else if (neue_richtung == 4) {
				schlange.gehnachoben();
			}

			gameover = schlange.schlangenbewegung();

			if (schlange.aufsammeln(schlangenstueck)) {
				apfel.play(1, 1, false);
				schlangenstueck = Schlangenstueck();
				//vllt hier das ger�usch zum aufsammeln??
			}

		}

		//Was passiert bei den verschieden Richtungen
		
		/*if (updatezaehler % geschwindigkeit == 0) {
			if (richtung == 1) {
				x_2 = x_1;
				y_2 = y_1;
				x_1 = x;
				y_1 = y;
				x = x - schrittweite;
			}
			else if (richtung == 2) {
				x_2 = x_1;
				y_2 = y_1;
				x_1 = x;
				y_1 = y;
				x = x + schrittweite;
			}
			else if (richtung == 3) {
				x_2 = x_1;
				y_2 = y_1;
				x_1 = x;
				y_1 = y;
				y = y + schrittweite;
			}
			else if (richtung == 4) {
				x_2 = x_1;
				y_2 = y_1;
				x_1 = x;
				y_1 = y;
				y = y - schrittweite;
			}
			
		}*/

		




		//geh�rt zur alten schlange!!!!!!!
		//neuen Stein erzeugen wenn die Schlange die gleichen x, y Koordinate hat, Geschwindigkeitsanpassung bei 5 zus�tzlichen Steinen
		if (anzahlsteine == 0) {

			stein_x = (rand() % 800 / schrittweite - 1) * schrittweite;
			stein_y = (rand() % 600 / schrittweite -1) * schrittweite;
			anzahlsteine = anzahlsteine + 1;
			//hinderniss_x = (rand() % 159) * 5;
			//hinderniss_y = (rand() % 159) * 5;
			//anzahl_hindernisse = anzahl_hindernisse + 1;
		}


		if (x == stein_x && y == stein_y) {



			ergaenzung_x = stein_x;
			ergaenzung_y = stein_y;
			ergaenzung_farbe = 
			anzahlsteine = 0;
			anzahl_essen = anzahl_essen + 1;

			if (anzahl_essen % 5 == 0) {

				geschwindigkeit = geschwindigkeit - 1;			//Einteilung in 5 Geschwindigkeitstufen 

				if (geschwindigkeit == 0) {
					//was soll dann passieren?? Spiel gewonnen? oder bei Geschwindigkeit = 1 lassen?				W�rde die bei 1 lassen und beliebig lang laufen lassen
				}
			}
			
		} else {
			anzahlsteine = 1;
		}
	}
	
};

// C++ Hauptprogramm
int main()
{
	srand(time(0));				//das die Zufallszahlen wirklich zuf�llig sind 

	GameWindow window;
	window.show();
	
}


//Version Catrin17.10.22

/*
TO-DO 

- Gr��enverh�ltnisse --> Variable 
- (Anfangsbildschirm --> Au�enger�st )
- Hindernisse hinzuf�gen die bleiben (grau)
- Sterbebedingung --> Funktion, die aufgerufen wird. --> Gameover
- Verschiedene Power Ups: Mehrer Punkte oder Punkteabzug
- Rechts: Men� (Geschwindigkeit, Punktestand, Lautst�rkeeinstellung)

*/