#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>
#include <stdlib.h>
#include<list>

class Schlangenstueck {				//class Schlangenstuecke
public:

	int x = 100;
	int y = 100;
	Gosu::Color farbe = Gosu::Color::GREEN;

	int geschwindigkeit = 30;
	int richtung = 0;

	Schlangenstueck() {

	}

	Schlangenstueck(int x, int y) {
		this->x = x;
		this->y = y;
	}

	Schlangenstueck(const Schlangenstueck& copy) {
		*this = copy;
	}

};

class Schlange {				//class Schlange 
public:
	int spielfeld_x = 800;
	int spielfeld_y = 600;
	int schrittweite = 5;

	int x = 70;					//Schlangenstartwert
	int y = 50;
	Gosu::Color farbe = Gosu::Color::GREEN;
	int leben = 3;				//durch Sonderteile Leben dazugewinnen? Oder Punkte abziehen wenn man ein Leben verliert?

	int geschwindigkeit = 100;	//Geschwindigkeitsstartwert
	int richtung = 0;

	std::list<Schlangenstueck> koerper = {Schlangenstueck(75, 50), Schlangenstueck(80,50)};

	void schlangenbewegung() {			//Bewegungsausf�hrung in Abh�ngigkeit der Richtung

		auto itr1 = koerper.begin();					//noch in Arbeit 
		for (auto itr2 = itr1++; itr1 != koerper.end(); itr2 = itr1++)
		{
			// do stuff
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

};

Gosu::Image hintergrundbild("Hintergrundbild.png");
Gosu::Sample musik("Hintergrundmusik.mp3");

class GameWindow : public Gosu::Window
{
public:

	GameWindow()
		: Window(1000, 600)
	{
		set_caption("Snake");
	}
	
	Schlange schlange = Schlange();
	Schlangenstueck schlangenstueck = Schlangenstueck();
	int x = 0;
	int y = 0;
	int x_1 = 0;
	int y_1 = 5;
	int x_2 = 0;
	int y_2 = 10;
	int updatezaehler = 0;
	int geschwindigkeit = 30;
	int richtung = 0;
	int anzahlsteine = 0;
	int stein_x = 60;
	int stein_y = 55;
	int ergaenzung_x = 0;
	int ergaenzung_y = 0;
	int anzahl_essen = 0;


	

	

	// Wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		/*graphics().draw_line(
			10, 20, Gosu::Color::RED,
			200, 100, Gosu::Color::GREEN,
			0.0
		);*/

		graphics().draw_quad(				//Schlangenkopf (class)
			schlange.x, schlange.y, schlange.farbe,
			schlange.x, schlange.y + 5, schlange.farbe,
			schlange.x + 5, schlange.y, schlange.farbe,
			schlange.x + 5, schlange.y + 5, schlange.farbe,
			0.0
		);

		for (auto it = schlange.koerper.begin(); it != schlange.koerper.end(); it++) {

		graphics().draw_quad(				//Schlangenstueck (class)
			it->x, it->y, it->farbe,
			it->x, it->y + 5, it->farbe,
			it->x + 5, it->y, it->farbe,
			it->x + 5, it->y + 5, it->farbe,
			0.0
		);
		}




		
		graphics().draw_quad(				//Schlangenkopf
			x, y, Gosu::Color::BLUE,
			x, y + 5, Gosu::Color::BLUE,
			x + 5, y, Gosu::Color::BLUE,
			x + 5, y + 5, Gosu::Color::BLUE,
			0.0
		);



		//nur zum Testen der Richtung Schlangengroessenerweiterung 
		graphics().draw_quad(				//Schlange+1
			x_1, y_1, Gosu::Color::BLUE,
			x_1, y_1 + 5, Gosu::Color::BLUE,
			x_1 + 5, y_1, Gosu::Color::BLUE,
			x_1 + 5, y_1 + 5, Gosu::Color::BLUE,
			0.0
		);
		graphics().draw_quad(				//Schlange+2
			x_2, y_2, Gosu::Color::BLUE,
			x_2, y_2 + 5, Gosu::Color::BLUE,
			x_2 + 5, y_2, Gosu::Color::BLUE,
			x_2 + 5, y_2 + 5, Gosu::Color::BLUE,
			0.0
		);



		graphics().draw_quad(				//Essensstein
			stein_x, stein_y, Gosu::Color::YELLOW,
			stein_x, stein_y + 5, Gosu::Color::YELLOW,
			stein_x + 5, stein_y, Gosu::Color::YELLOW,
			stein_x + 5, stein_y + 5, Gosu::Color::YELLOW,
			0.0
		);

		graphics().draw_quad(				//Menuefeld
			801, 0, Gosu::Color::GRAY,
			801, 601, Gosu::Color::GRAY,
			1000, 0, Gosu::Color::GRAY,
			1000, 601, Gosu::Color::GRAY,
			0.0
		);
			
		//hintergrundbild.draw(0, 0, 0, 1, 1, Gosu::AlphaMode::AM_INTERPOLATE);


	}
	
	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		//musik.play(40, 3, 1);
		//Randbetrachtung
		if (x == 800) {
			x = 0;
		}
		else if (x == -5) {
			x = 795;
		}
		else if (y == 600) {
			y = 0;
		}
		else if (y == -5) {
			y = 595;
		}
		

		updatezaehler = updatezaehler + 1;	//Zaehlt wie oft update aufgerufen wird, fuer Geschwindigkeitsanpassung(FUER BEIDE)
		//Was passiert bei den Verschieden Richtungen (class)
		if (updatezaehler % schlange.geschwindigkeit == 0) {
			schlange.schlangenbewegung();

		}

		//Was passiert bei den verschieden Richtungen
		
		if (updatezaehler % geschwindigkeit == 0) {
			if (richtung == 1) {
				x_2 = x_1;
				y_2 = y_1;
				x_1 = x;
				y_1 = y;
				x = x - 5;
			}
			else if (richtung == 2) {
				x_2 = x_1;
				y_2 = y_1;
				x_1 = x;
				y_1 = y;
				x = x + 5;
			}
			else if (richtung == 3) {
				x_2 = x_1;
				y_2 = y_1;
				x_1 = x;
				y_1 = y;
				y = y + 5;
			}
			else if (richtung == 4) {
				x_2 = x_1;
				y_2 = y_1;
				x_1 = x;
				y_1 = y;
				y = y - 5;
			}
			
		}

		


		//Pfeilzuordnungen + Pausenfunktion + wenn man in die Schlange laufen will wird die Richtung beibehalten
		if (input().down(Gosu::KB_LEFT)) {
			//x = x - 5;
			schlange.gehlinks();
			if (richtung == 2) {
				richtung = 2;

			}
			else {
				richtung = 1;
			}
			
		}
		else if (input().down(Gosu::KB_RIGHT)) {
			schlange.gehrechts();
			//x = x + 5;
			if (richtung == 1) {
				richtung = 1;
			}
			else {
				richtung = 2;
			}
			
		}
		else if (input().down(Gosu::KB_DOWN)) {
			schlange.gehnachunten();
			if (richtung == 4) {
				richtung = 4;
			}
			else {
				richtung = 3;

			}
			
		}
		else if (input().down(Gosu::KB_UP)) {
			schlange.gehnachoben();
			if (richtung == 3) {
				richtung = 3;
			}
			else {
				richtung = 4;
			}

		}
		else if (input().down(Gosu::KB_SPACE)) {
			schlange.pause();
			richtung = 0;
		}


		//neuen Stein erzeugen wenn die Schlange die gleichen x, y Koordinate hat, Geschwindigkeitsanpassung bei 5 zus�tzlichen Steinen
		if (anzahlsteine == 0) {

			stein_x = (rand() % 159) * 5;
			stein_y = (rand() % 119) * 5;
			anzahlsteine = anzahlsteine + 1;
		}


		if (x == stein_x && y == stein_y) {

			ergaenzung_x = stein_x;
			ergaenzung_y = stein_y;
			anzahlsteine = 0;
			anzahl_essen = anzahl_essen + 1;

			if (anzahl_essen % 5 == 0) {

				geschwindigkeit = geschwindigkeit - 1;

				if (geschwindigkeit == 0) {
					//was soll dann passieren?? Spiel gewonnen? oder bei Geschwindigkeit = 1 lassen?
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
	GameWindow window;
	window.show();
}


//Version Catrin