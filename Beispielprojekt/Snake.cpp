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
		int farbwahl = (rand() % 5);

		if(farbwahl == 0){

			farbe = Gosu::Color::GREEN;

		}
		else if (farbwahl == 1) {

			farbe = Gosu::Color::BLUE;

		}
		else if (farbwahl == 2) {

			farbe = Gosu::Color::YELLOW;
		}
		else if (farbwahl == 3) {

			farbe = Gosu::Color::FUCHSIA;
		}
		else if (farbwahl == 4) {

			farbe = Gosu::Color::AQUA;
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


	void schlangenbewegung() {			//Bewegungsausführung in Abhängigkeit der Richtung

		/*auto itr1 = map.begin();
		for (auto itr2 = itr1++; itr1 != map.end(); itr2 = itr1++)
		{
			// do stuff
		}*/


		auto vorderer_teil = koerper.rbegin();					//Schlangenstücke hinterherlaufen lassen
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
Gosu::Sample gameover_song("Game-Over.mp3");
Gosu::Sample apfel("Apfel essen.mp3");

Gosu::Font bla(10,"Pixeled.ttf");


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
	int richtung = 0;
	int neue_richtung = 0;
	Gosu::Color ergaenzung_farbe = Gosu::Color::GREEN;
	int schrittweite = 10;

	bool schon_gedrueckt = false;
	bool farbmodus_gedrueckt = false;

	//int anzahl_essen = 0;								//ausgeben
	int anzahl_hindernisse = 0;							//ausgeben
	int hinderniss_x;
	int hinderniss_y;


	bool gameover = false;								//für die Sterbefunktion
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
		

		//Lautstärkeicons

		bla.draw_text("Volume:", 810, 300, 3, 3, 3, Gosu::Color::GREEN, Gosu::BlendMode::BM_ADD);

		musikaus.draw(800, 320, 3,0.3,0.3);
		musikleise.draw(850, 320, 3,0.3,0.3);
		musiklaut.draw(900, 320,3, 0.3 ,0.3);


		//Geschwindigkeitsanzeige

		bla.draw_text("Speed: ", 810, 200, 3, 3, 3, Gosu::Color::GREEN, Gosu::BlendMode::BM_ADD);

		if (( schlange.geschwindigkeit ==9) || (schlange.geschwindigkeit == 10)){
			v910.draw(810, 220, 3, 0.5, 0.5);
		};
		if (( schlange.geschwindigkeit ==7) || (schlange.geschwindigkeit == 8)){
			v78.draw(810, 220, 3, 0.5, 0.5);
		};
		if ((schlange.geschwindigkeit == 5) || (schlange.geschwindigkeit == 6)){
			v56.draw(810, 220, 3, 0.5, 0.5);
		};
		if ((schlange.geschwindigkeit==3) || (schlange.geschwindigkeit == 4)){
			v34.draw(810, 220, 3, 0.5, 0.5);
		};
		if ((schlange.geschwindigkeit==1) || (schlange.geschwindigkeit == 2)){
			v12.draw(810, 220, 3, 0.5, 0.5);
		};

		//Levelanzeige

		if (schlange.farbmodus)
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


		//printf("%d \n", schlange.geschwindigkeit);
		//Lautstärkeeinstellung

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

		for (auto hindernis : hindernisse)
		{
			if (hindernis.hindernis_getroffen(schlange))
			{
				gameover = true;
				break;
			};

		}
		if (gameover) {				
			
			//gameover_song.play();
			hindernisse.clear();
		};



		//Pfeilzuordnungen + Pausenfunktion + wenn man in die Schlange laufen will wird die Richtung beibehalten

		if (input().down(Gosu::KB_F) && farbmodus_gedrueckt == false) {

			farbmodus_gedrueckt = true;
			if (schlange.farbmodus) {
				schlange.farbmodus = false;
			}
			else {
				schlange.farbmodus_aktivieren();
			}
		}
		if (input().down(Gosu::KB_F) == false && farbmodus_gedrueckt == true)
			{
				farbmodus_gedrueckt = false;
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
			neue_richtung = 0; //geändert von richtung
		
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
				punktestand = (schlange.koerper.size() * 5) - 10;		//fängt er bei 0 an ?? das erste hat er nicht mitgezählt, vorher 15...vllt reagiertr er aber auch nicht weil die schlangengröße zu dem zeitpunkt noch nicht verlängert ist 
				//printf("%d ", punktestand);
				if (schlange.farbmodus == true) {						//mehr punkte im Farbmodus, funktioniert noch nicht, weil auch die Farbumstellung noch nicht immer klappt vllt 
					punktestand = punktestand + 5;
				}
				

				schlangenstueck = Schlangenstueck();
				hindernisse.push_back(hindernis());

				if (punktestand > 10) { hindernisse.push_back(hindernis()); };
				if (punktestand > 20) { hindernisse.push_back(hindernis()); };
			}
			gameover = !schlange.lebt;

		}



	}
	
};

//--------------------------------------------------------MAIN----------------------------------------------------

// C++ Hauptprogramm
int main()
{
	srand(time(0));				//das die Zufallszahlen wirklich zufällig sind 

	GameWindow window;
	window.show();
	
}


//VersionCatrin 18.10.22

/*
TO-DO 

- Geschwindigkeitanpassungsfunktion
- level 2:Farbwahl

- Soundeffekte (essen und sterben)
- Verschiedene Power Ups: Mehrer Punkte oder Punkteabzug

- Rechts: Menü (Punktestand)
- Bugs: Punktestand zurücksetzen beim Neustart , Farbmodus klapp noch nicht und mit Anzeige verküpfen, mehr Punkte im Farbmodus


*/