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
	bool farbmodus = false;

	int geschwindigkeit = 10;	//Geschwindigkeitsstartwert
	int richtung = 0;
	bool lebt = true;

	std::list<Schlangenstueck> koerper = {Schlangenstueck(410, 300, Gosu::Color::GREEN), Schlangenstueck(420,300, Gosu::Color::GREEN), Schlangenstueck(430,300, Gosu::Color::GREEN)};
	std::list<Schlangenstueck> zwischenspeicher = {};


	void schlangenbewegung() {			//Bewegungsausf�hrung in Abh�ngigkeit der Richtung

		/*auto itr1 = map.begin();
		for (auto itr2 = itr1++; itr1 != map.end(); itr2 = itr1++)
		{
			// do stuff
		}*/


		auto vorderer_teil = koerper.rbegin();					//Schlangenst�cke hinterherlaufen lassen
		if (richtung != 0) {
			for (auto hinterer_teil = vorderer_teil++; vorderer_teil != koerper.rend(); hinterer_teil = vorderer_teil++)
			{
				//printf("%d ", vorderer_teil->x);		//nur zum Testen
				hinterer_teil->x = vorderer_teil->x;
				hinterer_teil->y = vorderer_teil->y;

			}

			//printf("\n"); //nur zum Testen
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
		lebt = !schlange_getroffen(x, y);

	}




	bool aufsammeln(Schlangenstueck schlangenstueck) {

		
		if (zwischenspeicher.size() > 0 && zwischenspeicher.front().x == koerper.back().x && zwischenspeicher.front().y == koerper.back().y) {
			koerper.push_back(zwischenspeicher.front());
			zwischenspeicher.pop_front();

			if (geschwindigkeit != 1 && (koerper.size() - 3) % 5 == 0) {
				geschwindigkeit = geschwindigkeit - 1;
				//printf("%d ", geschwindigkeit);
			}
			
		}	

		if (schlangenstueck.x == x && schlangenstueck.y == y) {
			if (farbmodus == false || schlangenstueck.farbe == farbe) {
				zwischenspeicher.push_back(schlangenstueck);

			}
			else {
				lebt = false;
			}
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

	void farbmodus_aktivieren() {
		umfaerben(Gosu::Color::GREEN);
		farbmodus = true;

	}

	void umfaerben(Gosu::Color farbe) {
		for (auto it = koerper.begin(); it != koerper.end(); it++) {
			it->farbe = farbe;
		}
		for (auto it = zwischenspeicher.begin(); it != zwischenspeicher.end(); it++) {
			it->farbe = farbe;
		}
		this->farbe = farbe;

	}


};


//--------------------------------------------------AUDIO UND GRAFIKEN-------------------------------------------------------------

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
Gosu::Image level1("level1.png");
Gosu::Image level2("level2.png");

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
	
//--------------------------------------------------INITIALISIERUNG WERTE--------------------------------------------------------

	Schlange schlange = Schlange();
	Schlangenstueck schlangenstueck = Schlangenstueck();
	

	int x = 0;
	int y = 0;
	int updatezaehler = 0;
	int geschwindigkeit = 30;							
	int richtung = 0;
	int neue_richtung = 0;
	int anzahlsteine = 0;
	int stein_x = 60;
	int stein_y = 70;
	int ergaenzung_x = 0;
	int ergaenzung_y = 0;
	Gosu::Color ergaenzung_farbe = Gosu::Color::GREEN;
	int schrittweite = 10;
	bool schon_gedrueckt = false;

	int anzahl_essen = 0;								//ausgeben
	int anzahl_hindernisse = 0;							//ausgeben
	int hinderniss_x;
	int hinderniss_y;

	bool gameover = false;								//f�r die Sterbefunktion
	int punktestand = 0;


	//------------------------------------------------------------DRAW----------------------------------------------------------------------
	void draw() override
	{

		//Bilder
		hintergrundbild.draw(240, 150, 0, 1, 1);									
		wall.draw(800, 0, 3, 0.4, 0.6, Gosu::Color::WHITE, Gosu::BlendMode::BM_INTERPOLATE);
		menu.draw(830, 0, 3, 0.5, 0.5);
		

		//Lautst�rkeicons

		bla.draw_text("Volume:", 810, 300, 3, 3, 3, Gosu::Color::GREEN, Gosu::BlendMode::BM_ADD);

		musikaus.draw(800, 320, 3,0.3,0.3);
		musikleise.draw(850, 320, 3,0.3,0.3);
		musiklaut.draw(900, 320,3, 0.3 ,0.3);

		//Geschwindigkeitsanzeige

		bla.draw_text("Speed: ", 810, 200, 3, 3, 3, Gosu::Color::GREEN, Gosu::BlendMode::BM_ADD);

		if ((8 < schlange.geschwindigkeit) && (schlange.geschwindigkeit <= 10)){
			v910.draw(810, 220, 3, 0.5, 0.5);
		};
		if ((6 < schlange.geschwindigkeit) && (schlange.geschwindigkeit <= 8)){
			v78.draw(810, 220, 3, 0.5, 0.5);
		};
		if ((4 < schlange.geschwindigkeit) && (schlange.geschwindigkeit <= 6)){
			v56.draw(810, 220, 3, 0.5, 0.5);
		};
		if ((2 < schlange.geschwindigkeit) && (schlange.geschwindigkeit <= 4)){
			v34.draw(810, 220, 3, 0.5, 0.5);
		};
		if ((1 <= schlange.geschwindigkeit) && (schlange.geschwindigkeit <= 2)){
			v12.draw(810, 220, 3, 0.5, 0.5);
		};

		//Levelanzeige

		if (punktestand >= 2)		// ist nur zwei um gut testen zu k�nnen  
		{
			level2.draw(810, 430, 3, 1, 1);
		}
		else
		{
			level1.draw(810, 400, 3, 1, 1);
		}

		//Scoreanzeige

		bla.draw_text("Score: ", 810, 110, 3, 3, 3,Gosu::Color::GREEN, Gosu::BlendMode::BM_ADD);
		//bla.draw_text(punktestand, 840, 110, 3, 3, 3);  //const string!

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

		for (auto it = schlange.zwischenspeicher.begin(); it != schlange.zwischenspeicher.end(); it++) {

			graphics().draw_quad(				//Schlangenstueck vom Zwischenspeicher (class)
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
			hinderniss_x, hinderniss_y, Gosu::Color::GRAY,
			hinderniss_x, hinderniss_y + schrittweite, Gosu::Color::GRAY,
			hinderniss_x + schrittweite, hinderniss_y, Gosu::Color::GRAY,
			hinderniss_x + schrittweite, hinderniss_y + schrittweite, Gosu::Color::GRAY, 0.0
		);

		if (gameover) {
			gameover_screen.draw(0, 0, 2, 1.18, 1.18);
		}
	}
	
	//----------------------------------------------------------UPDATE-------------------------------------------------------------------

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		musik.play(true);		//Hintergrundmusik in Endlosschleife
		// 
		//Pfeilzuordnungen + Pausenfunktion + wenn man in die Schlange laufen will wird die Richtung beibehalten

		if (input().down(Gosu::KB_F)) {
			
			if (schlange.farbmodus) {
				schlange.farbmodus = false;
			}
			else {
				schlange.farbmodus_aktivieren();
			}

		}
		if (schon_gedrueckt == false && input().down(Gosu::KB_SPACE) && schlange.farbmodus) {
			schon_gedrueckt = true;



			if (schlange.farbe == Gosu::Color::GREEN) {
			
				schlange.umfaerben(Gosu::Color::BLUE);
			}
			else if (schlange.farbe == Gosu::Color::BLUE) {
				schlange.umfaerben(Gosu::Color::YELLOW);
			}
			else if (schlange.farbe == Gosu::Color::YELLOW){
				schlange.umfaerben(Gosu::Color::FUCHSIA);
		
			}
			else if (schlange.farbe == Gosu::Color::FUCHSIA) {
				schlange.umfaerben(Gosu::Color::AQUA);
			}
			else if (schlange.farbe == Gosu::Color::AQUA) {
				schlange.umfaerben(Gosu::Color::GREEN);
			}


		}
		if(input().down(Gosu::KB_SPACE) == false) {

			schon_gedrueckt = false;
		}
		else {			
			if (gameover) {
				schlange = Schlange();
				neue_richtung = 0;
				gameover = false;
			}

		}


		

		if (input().down(Gosu::KB_LEFT)) {
			//x = x - schrittweite;
			
			neue_richtung = 1;

			
		}
		else if (input().down(Gosu::KB_RIGHT)) {
			neue_richtung = 2;
			//x = x + schrittweite;

			
		}
		else if (input().down(Gosu::KB_DOWN)) {
			neue_richtung = 3;

			
		}
		else if (input().down(Gosu::KB_UP)) {
			neue_richtung = 4;


		}
		else if (input().down(Gosu::KB_P)) {

			schlange.pause();
			neue_richtung = 0; //ge�ndert von richtung
		
		}

		if (gameover) {
					return;
				}

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

			schlange.schlangenbewegung();

			if (schlange.aufsammeln(schlangenstueck)) {
				apfel.play(1, 1, false);
				punktestand = (schlange.koerper.size() * 5) - 15;
				//printf("%d ", punktestand);
				schlangenstueck = Schlangenstueck();
			}
			gameover = !schlange.lebt;

		}


		//geh�rt zur alten schlange!!!!!!!
		//neuen Stein erzeugen wenn die Schlange die gleichen x, y Koordinate hat, Geschwindigkeitsanpassung bei 5 zus�tzlichen Steinen
		/*if (anzahlsteine == 0) {

			stein_x = (rand() % 800 / schrittweite - 1) * schrittweite;
			stein_y = (rand() % 600 / schrittweite -1) * schrittweite;
			anzahlsteine = anzahlsteine + 1;

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
		}*/
	}
	
};

//--------------------------------------------------------MAIN----------------------------------------------------

// C++ Hauptprogramm
int main()
{
	srand(time(0));				//das die Zufallszahlen wirklich zuf�llig sind 

	GameWindow window;
	window.show();
	
}


//Gemeinsame Version17.10.22

/*
TO-DO 

- Geschwindigkeitanpassungsfunktion
- level 2:Farbwahl
- Hindernisse hinzuf�gen die bleiben (grau)
- Sterbebedingung --> Funktion, die aufgerufen wird (hindernisse)
- Verschiedene Power Ups: Mehrer Punkte oder Punkteabzug
- Rechts: Men� ( Punktestand, Lautst�rkeeinstellung, level1 und level2)

*/