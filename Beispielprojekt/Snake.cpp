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
	

	Schlangenstueck() {															//Konstruktor

		
		x = (rand() % ((800 / schrittweite) - 1) * schrittweite);				//Erzeugung eines Schlangenstücks an einem zufälligen Ort
		y = (rand() % ((600 / schrittweite) - 1) * schrittweite);
		int farbwahl = (rand() % 5);											//mit zufälliger Farbe

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

	Schlangenstueck(int x, int y, Gosu::Color farbe) {							//Konstruktor, konkretes Schlangenstück 
		this->x = x;
		this->y = y;
		this->farbe = farbe;
	}

	Schlangenstueck(const Schlangenstueck& copy) {								//Konstruktor, für die Liste
		*this = copy;
	}

};

class Schlange {								//class Schlange 
public:
	int spielfeld_x = 800;			
	int spielfeld_y = 600;
	int schrittweite = 10;

	int x = 400;								//Schlangenstartwert für den Schlangenkopf
	int y = 300;
	Gosu::Color farbe = Gosu::Color::GREEN;		//Im Farbmodus Farbe für ganze Schlange, ansonsten nur für den Kopf

	bool farbmodus = false;

	int geschwindigkeit = 10;					//Geschwindigkeitsstartwert
	int richtung = 0;
	bool lebt = true;

	std::list<Schlangenstueck> koerper = {Schlangenstueck(410, 300, Gosu::Color::GREEN), Schlangenstueck(420,300, Gosu::Color::GREEN), Schlangenstueck(430,300, Gosu::Color::GREEN)};
	std::list<Schlangenstueck> zwischenspeicher = {};			//Zwischenspeicher für gefressene Schlangenstücke


	void schlangenbewegung() {									//Bewegungsausführung in Abhängigkeit der Richtung

		/*auto itr1 = map.begin();
		for (auto itr2 = itr1++; itr1 != map.end(); itr2 = itr1++)
		{
			// do stuff
		}*/


		auto vorderer_teil = koerper.rbegin();					//Schlangenstückkoordinaten schreiben vom vorderen Stück in das hintere Stück, Bewegung der Liste, Richtung egal weil hinterherlaufen
		if (richtung != 0) {									//Schleife nur machen wenn Schlange in Bewegung									
			for (auto hinterer_teil = vorderer_teil++; vorderer_teil != koerper.rend(); hinterer_teil = vorderer_teil++)
			{
				//printf("%d ", vorderer_teil->x);				//nur zum Testen
				hinterer_teil->x = vorderer_teil->x;
				hinterer_teil->y = vorderer_teil->y;

			}

			//printf("\n");										//nur zum Testen
			koerper.front().x = x;								//Koordinatenübergabe vom Kopf an das erste Listenstück 
			koerper.front().y = y;
		}

		if (richtung == 1) {									//Bewegung des Schlangenkopfes, Ausführen der Bewegung 

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
		ueberprueferaender();									//Schlange kann durch Wände laufen 
		lebt = !schlange_getroffen(x, y);						//Überprüfung ob wir uns beim Bewegen getroffen haben, (x,y) Koordinaten des Kopfes gleich mit einem Element der Liste

	}

	bool aufsammeln(Schlangenstueck schlangenstueck) {			//Aufsammelfunktion
		if (zwischenspeicher.size() > 0 && zwischenspeicher.front().x == koerper.back().x && zwischenspeicher.front().y == koerper.back().y) {
			koerper.push_back(zwischenspeicher.front());		//erstes Zwischenspeicherelement anhängen wenn auf letztem Schlangenstück
			zwischenspeicher.pop_front();

			if (geschwindigkeit != 1 && (koerper.size() - 3) % 5 == 0) {	//Geschwindigkeitsanpassung, passiert erst wenn ein Teil angehängt also 1 und nicht 0 
				geschwindigkeit = geschwindigkeit - 1;
				//printf("%d ", geschwindigkeit);
			}
		}	

		if (schlangenstueck.x == x && schlangenstueck.y == y) {				//aufnehmen in den Zwischenspeicher mit Farbmodussonderfall
			if (farbmodus == false || schlangenstueck.farbe == farbe) {
				zwischenspeicher.push_back(schlangenstueck);
			}
			else {
				lebt = false;
			}
			return true;										//um zu wissen wann ich etwas aufgesammelt habe, brauche ich für andere Aktionen
		}
		return false;
	}


	void gehlinks() {				//Richtungsfestlegung
		if (richtung != 2) {		//ausschließen des Rückwärtsgehens
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

	void ueberprueferaender() {					//Randbetrachtung
		if (x == spielfeld_x) {
			x = 0;								//auf der anderen Seite wieder rauskommen
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

	bool schlange_getroffen(int x, int y) {		//in einer Schleife schauen ob (x,y) Koordinate von Schlangenkopf gleich mit einem Schlangenteil, (x,y) allgemein auf für andere (x,y) benutzbar 
		for (auto it = koerper.begin(); it != koerper.end(); it++) {	//Schlangenkopf wird nicht berücksichtigt
																		//nur Schlangenkörper wird durchgegangen
			if (it->x == x && it->y == y) {
				return true;
			}
		}
		return false;

	}


	void farbmodus_aktivieren() {				//Setzt Frabmodus auf aktiv und macht die Schlange einfarbig (immer grün)
		umfaerben(Gosu::Color::GREEN);
		farbmodus = true;
	}

	void umfaerben(Gosu::Color farbe) {			//macht die Schlange einfarbig in einer beliebigen Farbe
		for (auto it = koerper.begin(); it != koerper.end(); it++) {
			it->farbe = farbe;					//Körper einfärben 
		}
		for (auto it = zwischenspeicher.begin(); it != zwischenspeicher.end(); it++) {
			it->farbe = farbe;					//Zwischenspeicher einfärben
		}

		this->farbe = farbe;					//Kopf einfärben 


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
		if ((s.x == this->x) && (s.y == this->y)){
			return true;
		}
		else{
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
Gosu::Image farbmodus("farbmodus.png");
Gosu::Image dunkelmodus("dunkelmodus.png");
Gosu::Image highscore_bild("highscore.png");

Gosu::Image tutorial1("tutorial1.png");
Gosu::Image tutorial2("tutorial2.png");
Gosu::Image tutorial3("tutorial3.png");
Gosu::Image neustart("neustart.png");
Gosu::Image aua("aua.png");


Gosu::Song musik("Hintergrundmusik.mp3");
Gosu::Sample gameover_song("Game-Over.mp3");
Gosu::Sample verloren("verloren.wav");
Gosu::Sample apfel("Apfel essen.mp3");

Gosu::Font bla(15,"Pixeled.ttf");


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
	Schlangenstueck schlangenstueck = Schlangenstueck();	//nur ein (neues) Schlangenstück, das das man aufsammeln kann
	
	int updatezaehler = 0;						
	int richtung = 0;
	int neue_richtung = 0;
	int schrittweite = 10;
	int anzahl_hindernisse = 0;							//ausgeben
	int hinderniss_x;
	int hinderniss_y;
	int punktestand = 0;
	int mitzaehler = 0;

	bool schon_gedrueckt = false;
	bool farbmodus_gedrueckt = false;
	bool gameover = false;								//für die Sterbefunktion
	bool liegt_drauf = false;

	double set_volume = 0.5;
	
	vector<int> highscore;
	int high = 0;

	vector<hindernis> hindernisse;

	//------------------------------------------------------------DRAW----------------------------------------------------------------------
	void draw() override
	{

		//Bilder
		hintergrundbild.draw(240, 150, 0, 1, 1);									
		wall.draw(800, 0, 3, 0.4, 0.6, Gosu::Color::WHITE, Gosu::BlendMode::BM_INTERPOLATE);
		menu.draw(830, 0, 3, 0.5, 0.5);
		

		//Lautstärkeicons

		bla.draw_text("Volume:", 810, 300, 3, 3, 3, Gosu::Color::GREEN);

		musikaus.draw(800, 320, 3,0.3,0.3);
		musikleise.draw(850, 320, 3,0.3,0.3);
		musiklaut.draw(900, 320,3, 0.3 ,0.3);


		//Geschwindigkeitsanzeige

		bla.draw_text("Speed: ", 810, 200, 3, 3, 3, Gosu::Color::GREEN);

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

		if (schlange.farbmodus){
			farbmodus.draw(810, 450, 3, 1, 1);
		}
		else{
			dunkelmodus.draw(810, 450, 3, 1, 1);
		};

		//Scoreanzeige

		bla.draw_text("Score: ", 810, 110, 3, 3, 3, Gosu::Color::GREEN);
		bla.draw_text(to_string(punktestand), 820, 145, 3, 3, 3, Gosu::Color::GREEN);
		bla.draw_text(to_string(high), 820, 500, 3,3,3,Gosu::Color::YELLOW);			
		highscore_bild.draw(870, 500, 3, 1, 1);

		//Schlangenkopf (class)

		graphics().draw_quad(					
			schlange.x, schlange.y, schlange.farbe,
			schlange.x, schlange.y + schlange.schrittweite, schlange.farbe,
			schlange.x + schlange.schrittweite, schlange.y, schlange.farbe,
			schlange.x + schlange.schrittweite, schlange.y + schlange.schrittweite, schlange.farbe,
			0.0
		);

		//Schlangenstueck vom Koerper (class)

		for (auto it = schlange.koerper.begin(); it != schlange.koerper.end(); it++) {

			graphics().draw_quad(				
				it->x, it->y, it->farbe,
				it->x, it->y + schlange.schrittweite, it->farbe,
				it->x + schlange.schrittweite, it->y, it->farbe,
				it->x + schlange.schrittweite, it->y + schlange.schrittweite, it->farbe,
				0.0
			);
		}

		//Schlangenstueck vom Zwischenspeicher (class)

		for (auto it = schlange.zwischenspeicher.begin(); it != schlange.zwischenspeicher.end(); it++) {

			graphics().draw_quad(				
				it->x, it->y, it->farbe,
				it->x, it->y + schlange.schrittweite, it->farbe,
				it->x + schlange.schrittweite, it->y, it->farbe,
				it->x + schlange.schrittweite, it->y + schlange.schrittweite, it->farbe,
				0.0
			);
		}

		//Schlangenstueck zum Essen (class)

		graphics().draw_quad(				
			schlangenstueck.x, schlangenstueck.y, schlangenstueck.farbe,
			schlangenstueck.x, schlangenstueck.y + schlangenstueck.schrittweite, schlangenstueck.farbe,
			schlangenstueck.x + schlangenstueck.schrittweite, schlangenstueck.y, schlangenstueck.farbe,
			schlangenstueck.x + schlangenstueck.schrittweite, schlangenstueck.y + schlangenstueck.schrittweite, schlangenstueck.farbe,
			0.0
		);

		//Hindernisse

		for (auto hindernis : hindernisse)
		{
			graphics().draw_quad(
				hindernis.x, hindernis.y, Gosu::Color::GRAY,
				hindernis.x, hindernis.y + schrittweite, Gosu::Color::GRAY,
				hindernis.x + schrittweite, hindernis.y, Gosu::Color::GRAY,
				hindernis.x + schrittweite, hindernis.y + schrittweite, Gosu::Color::GRAY, 0.0
			);
		};

		//Gameover Bildschirm

		if (gameover) {
			aua.draw(0, 0, 2, 1.65, 1.65);
			neustart.draw(600, 400, 3);
		}
			
		//Tutorial

		if (schlange.richtung == 0){
			tutorial1.draw(600, 400, -1);
		}
		if (punktestand == 5){
			tutorial2.draw(600, 400, -1);
		}
		if (punktestand == 10){
			tutorial3.draw(600, 400, -1);
		}
	}


	//----------------------------------------------------------UPDATE-------------------------------------------------------------------

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		//Lautstärkeeinstellung

		if (input().down(Gosu::MS_LEFT) && input().mouse_x() < 860 && input().mouse_x() > 800 && input().mouse_y() < 370 && input().mouse_y() > 340){
			set_volume = 0;
		};
		if (input().down(Gosu::MS_LEFT) && input().mouse_x() < 900 && input().mouse_x() > 860 && input().mouse_y() < 370 && input().mouse_y() > 340){
			set_volume = 0.5;
		};
		if (input().down(Gosu::MS_LEFT) && input().mouse_x() < 965 && input().mouse_x() > 910 && input().mouse_y() < 370 && input().mouse_y() > 340){
			set_volume = 1;
		};

		//Hintergrundmusik in Endlosschleife

		musik.set_volume(set_volume);
		musik.play(true);		

		for (auto hindernis : hindernisse)
		{
			if (hindernis.hindernis_getroffen(schlange)){
				gameover = true;
				break;
			};
		}

		for (auto i : highscore){
			if (high < i){
				high = i;
			}
		}
		if (gameover) {				
			highscore.push_back(punktestand);
			//verloren.play();
			hindernisse.clear();
		};


		//Farbmodus 

		if (input().down(Gosu::KB_F) && farbmodus_gedrueckt == false) {	//komme nur rein wenn Taste runtergedrückt wird und vorher noch nicht gedrückt war

			farbmodus_gedrueckt = true;									//verhindert das ich wieder in das obere if komme 
			if (schlange.farbmodus) {
				schlange.farbmodus = false;								//wenn die Taste geklickt wurde wird der Farbmodus geändert von true auf false
			}
			else {
				schlange.farbmodus_aktivieren();						// von false in true
			}
		}

		if (input().down(Gosu::KB_F) == false && farbmodus_gedrueckt == true)	//ist Taste F aktuell nicht gedrückt
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
		if(input().down(Gosu::KB_SPACE) == false) {			//ist Leertaste aktuell nicht gedrückt 
			schon_gedrueckt = false;
		} else {											//wenn Leertaste gedrückt und gameover, setzt Dinge zurück 	
			if (gameover) {
				schlange = Schlange();
				neue_richtung = 0;
				punktestand = 0;
				gameover = false;
			}
		}


		if (input().down(Gosu::KB_LEFT)) {		//welche Taste wurde zuletzt gedrückt 
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
			neue_richtung = 0;			//geändert von richtung
		}
		if (gameover) {
			mitzaehler = 0;
					return;				//wenn gameover gehe aus updatefunktion
				}

		updatezaehler = updatezaehler + 1;	//Zaehlt wie oft update aufgerufen wird, fuer Geschwindigkeitsanpassung(FUER BEIDE)
		//Was passiert bei den Verschieden Richtungen (class)
		if (updatezaehler % schlange.geschwindigkeit == 0) {				//Bewegung nur so oft ausführen wie die Geschwindigkeit vorgibt
			if (neue_richtung == 1) {										//gibt der Schlange die neue Richtung 
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
			schlange.schlangenbewegung();				//sorgt dafür das die Schlange sich bewegt 

			if (schlange.aufsammeln(schlangenstueck)) 
			{														//wenn der Schlangenkopf das Schlangenstück berührt, was passiert dann
				apfel.play(1, 1, false);
				punktestand = (schlange.koerper.size() * 5) - 10 + (mitzaehler * 5);		//Punkte pro Schlangenstück 
			
				if (schlange.farbmodus == true) {						//Sonderpunkte im Farbmodus pro Schlangenstück 
					punktestand = punktestand + 5;
					mitzaehler = mitzaehler + 1;
				}
				hindernisse.push_back(hindernis());
				if (punktestand > 30) { hindernisse.push_back(hindernis()); };
				if (punktestand > 60) { hindernisse.push_back(hindernis()); };

				do
				{
					schlangenstueck = Schlangenstueck();
					liegt_drauf = false;
					for (auto i : hindernisse)
					{
						if ((schlangenstueck.x == i.x) && (schlangenstueck.y == i.y)) {
							liegt_drauf = true;
							break;
						}
					}
				} while (liegt_drauf);
			}
			gameover = !schlange.lebt;				//gameover setzt oder nicht jenachdem ob die Schlange in dem updateablauf gestorben ist, im nächsten updatedurchlauf ist dann gameover
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


//Version 19.10.22.

