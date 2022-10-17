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

	bool essgeraeusch(int x, int y)
	{
		if (this->x == x && this->y == y){ return true;}
		else { return false; }
	}

	//Geschwindigkeitsanpassungsfunktion 
	//printf("%d ", geschwindigkeit); 

};

class hindernis
{
public: 
	int x;
	int y;
	int breite = 10;

	hindernis()
	{
		x = (rand() % ((800 / breite) - 1) * breite);
		y = (rand() % ((600 / breite) - 1) * breite);
	};

	bool hindernis_getroffen(Schlange s)
	{
		if ((s.x == this->x) && (s.y == this->y))
		{
			return true;
		}
		else
		{
			return false;
		}
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
Gosu::Image farbmodus("farbmodus.png");
Gosu::Image dunkelmodus("dunkelmodus.png");

Gosu::Song musik("Hintergrundmusik.mp3");
Gosu::Song gameover_song("Game-Over.mp3");
Gosu::Song apfel("Apfel essen.mp3");

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

	bool gameover = false;								//f�r die Sterbefunktion
	int punktestand = 0;
	double set_volume = 0.5;
	

	vector<hindernis> hindernisse;

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

		if (punktestand >= 2)
		{
			farbmodus.draw(810, 450, 3, 1, 1);
		}
		else
		{
			dunkelmodus.draw(810, 450, 3, 1, 1);
		};

		//Scoreanzeige

		bla.draw_text("Score: ", 810, 110, 3, 3, 3, Gosu::Color::GREEN, Gosu::BlendMode::BM_ADD);
		bla.draw_text(to_string(punktestand), 820, 145, 3, 3, 3, Gosu::Color::GREEN);

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

		for (auto hindernis : hindernisse)
		{
			graphics().draw_quad(			
				hindernis.x, hindernis.y, Gosu::Color::GRAY,
				hindernis.x, hindernis.y + schrittweite, Gosu::Color::GRAY,
				hindernis.x + schrittweite, hindernis.y, Gosu::Color::GRAY,
				hindernis.x + schrittweite, hindernis.y + schrittweite, Gosu::Color::GRAY, 0.0
			);
		};

		if (gameover) {
			gameover_screen.draw(0, 0, 2, 1.18, 1.18);
		}
	}
	
	//----------------------------------------------------------UPDATE-------------------------------------------------------------------

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		//Lautst�rkeeinstellung

		if (input().down(Gosu::MS_LEFT) && input().mouse_x() < 860 && input().mouse_x() > 800 && input().mouse_y() < 370 && input().mouse_y() > 340)
		{
			set_volume = 0;
		};
		if (input().down(Gosu::MS_LEFT) && input().mouse_x() < 900 && input().mouse_x() > 860 && input().mouse_y() < 370 && input().mouse_y() > 340)
		{
			set_volume = 0.5;
		};
		if (input().down(Gosu::MS_LEFT) && input().mouse_x() < 965 && input().mouse_x() > 910 && input().mouse_y() < 370 && input().mouse_y() > 340)
		{
			set_volume = 1;
		};

		musik.set_volume(set_volume);
		musik.play(true);		//Hintergrundmusik in Endlosschleife
		
		

		if (schlange.essgeraeusch(schlangenstueck.x, schlangenstueck.y))					//ist nur 1/6 Sekunde an, wie verl�ngern?
		{
			//musik.pause();
			//apfel.play(false);
			//void Gosu::sleep(100);
			//musik.play(true);
		}

		for (auto hindernis : hindernisse)
		{
			if (hindernis.hindernis_getroffen(schlange))
			{
				gameover = true;
				break;
			};

		}
		if (gameover){																	//das klappt noch nicht *************++++++++++++++++***************+
					musik.stop();
					gameover_song.set_volume(set_volume);
					gameover_song.play(false);
					hindernisse.clear();
				};


		
		//Pfeilzuordnungen + Pausenfunktion + wenn man in die Schlange laufen will wird die Richtung beibehalten

		punktestand = (schlange.koerper.size() * 5) - 15;

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
				
				schlangenstueck = Schlangenstueck();
				hindernisse.push_back(hindernis());

				if (punktestand > 10) { hindernisse.push_back(hindernis()); };
				if (punktestand > 20) { hindernisse.push_back(hindernis()); };
			}

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

- Soundeffekte (essen und sterben)
- Verschiedene Power Ups: Mehrer Punkte oder Punkteabzug
- Rechts: Men� (Punktestand)

*/