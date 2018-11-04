/*************************************************************************************/

//  Szkielet programu do tworzenia modelu sceny 3-D z wizualizacj� osi  
//  uk�adu wsp�rzednych

/*************************************************************************************/

#define _USE_MATH_DEFINES
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <cmath>
#include <math.h>

typedef float point3[3];

/*************************************************************************************/

// Funkcja rysuj�ca osie uk�adu wsp�rz�dnych
const int number_of_sections = 50;
point3 coordinates[number_of_sections][number_of_sections];
point3 tableOfColors[number_of_sections][number_of_sections];
int model = 1; // 1 - punkty, 2 - siatka, 3 - wype�nione tr�jk�ty
static GLfloat theta[] = { 0.0, 0.0, 0.0 }; // trzy k�ty obrotu 0-x, 1-y, 2-z

/*************************************************************************************/

void SpinEgg()
{
	float spinValue = 0.05;
	float angleValue = 180.0;
	theta[0] -= spinValue;
	if (theta[0] > angleValue) theta[0] -= angleValue;

	theta[1] -= spinValue;
	if (theta[1] > angleValue) theta[1] -= angleValue;

	theta[2] -= spinValue;
	if (theta[2] > angleValue) theta[2] -= angleValue;

	glutPostRedisplay(); //od�wie�enie zawarto�ci aktualnego okna
}

void MoveImageDown()
{
	int factor = 4;
	for (int i = 0; i < number_of_sections; ++i)
	{
		for (int j = 0; j < number_of_sections; ++j)
		{
			coordinates[i][j][1] -= factor;
		}
	}
}

float Color()
{
	float x = rand() % 100;
	return x / 100;
}

void FillTableOfColors()
{
	for (int i = 0; i < number_of_sections; ++i)
	{
		for (int j = 0; j < number_of_sections; ++j)
		{
			tableOfColors[i][j][0] = Color();
			tableOfColors[i][j][1] = Color();
			tableOfColors[i][j][2] = Color();
		}
	}
}

void PrintEgg()
{
	switch (model) {
	case 1:
		glBegin(GL_POINTS);  // rysowanie osi y
		for (int i = 0; i < number_of_sections; ++i)
		{
			for (int j = 0; j < number_of_sections; ++j)
			{
				glVertex3fv(coordinates[i][j]);
			}
		}
		glEnd();
		break;
	case 2:
		for (int i = 0; i < number_of_sections - 1; ++i)
		{
			for (int j = 0; j < number_of_sections - 1; ++j)
			{
				glBegin(GL_LINES);
				glVertex3fv(coordinates[i][j]);
				glVertex3fv(coordinates[i + 1][j]);
				glEnd();

				glBegin(GL_LINES);
				glVertex3fv(coordinates[i][j]);
				glVertex3fv(coordinates[i][j + 1]);
				glEnd();
			}
		}
		break;
	case 3:
		for (int i = 0; i < number_of_sections - 1; ++i)
		{
			for (int j = 0; j < number_of_sections - 1; ++j)
			{
				glBegin(GL_TRIANGLES);
				glColor3f(tableOfColors[i][j][0],
					tableOfColors[i][j][1], tableOfColors[i][j][2]);
				glVertex3fv(coordinates[i][j]);

				glColor3f(tableOfColors[i + 1][j][0],
					tableOfColors[i + 1][j][1], tableOfColors[i + 1][j][2]);
				glVertex3fv(coordinates[i + 1][j]);

				glColor3f(tableOfColors[i][j + 1][0],
					tableOfColors[i][j+1][1], tableOfColors[i][j + 1][2]);
				glVertex3fv(coordinates[i][j + 1]);
				glEnd();
				
				glBegin(GL_TRIANGLES);
				glColor3f(tableOfColors[i][j + 1][0],
					tableOfColors[i][j + 1][1], tableOfColors[i][j + 1][2]);
				glVertex3fv(coordinates[i][j + 1]);

				glColor3f(tableOfColors[i + 1][j][0],
					tableOfColors[i + 1][j][1], tableOfColors[i + 1][j][2]);
				glVertex3fv(coordinates[i+1][j]);

				glColor3f(tableOfColors[i + 1][j + 1][0],
					tableOfColors[i + 1][j + 1][1], tableOfColors[i + 1][j + 1][2]);
				glVertex3fv(coordinates[i + 1][j + 1]);
				glEnd();
			}
		}
		break;
	}
}

/*************************************************************************************/


void Axes(void)
{

	point3  x_min = { -5.0, 0.0, 0.0 };
	point3  x_max = { 5.0, 0.0, 0.0 };
	// pocz�tek i koniec obrazu osi x

	point3  y_min = { 0.0, -5.0, 0.0 };
	point3  y_max = { 0.0,  5.0, 0.0 };
	// pocz�tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -5.0 };
	point3  z_max = { 0.0, 0.0,  5.0 };
	//  pocz�tek i koniec obrazu osi y
	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x
	glVertex3fv(x_min);
	glVertex3fv(x_max);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y

	glVertex3fv(y_min);
	glVertex3fv(y_max);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z

	glVertex3fv(z_min);
	glVertex3fv(z_max);
	glEnd();

}

/*************************************************************************************/

// Funkcja okre�laj�ca co ma by� rysowane (zawsze wywo�ywana gdy trzeba 
// przerysowa� scen�)



void RenderScene(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz�cym

	glLoadIdentity();
	// Czyszczenie macierzy bie��cej
	// Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej wy�ej
	glColor3f(1.0f, 1.0f, 1.0f); // Ustawienie koloru rysowania na bia�y
	//glRotated(60.0, 1.0, 1.0, 1.0);  // Obr�t o 60 stopni


	glRotatef(theta[0], 1.0, 0.0, 0.0);

	glRotatef(theta[1], 0.0, 1.0, 0.0);

	glRotatef(theta[2], 0.0, 0.0, 1.0);

	PrintEgg();


		//glutWireTeapot(3.0); // Narysowanie obrazu czajnika do herbaty
	glFlush();
	// Przekazanie polece� rysuj�cych do wykonania


	glutSwapBuffers();
	//
}

float calculateX(float u, float v)
{
	return static_cast<float>((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * u*u - 45 * u)*cos(M_PI * v));
}

float calculateY(float u, float v)
{
	return static_cast<float>(160 * pow(u, 4) - 320 * pow(u, 3) + 160 * u*u);
}

float calculateZ(float u, float v)
{
	return static_cast<float>((-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * u*u - 45 * u)*sin(M_PI*v));
}

/*************************************************************************************/
void CreateNet(float square_side_begin, float square_side_end)
{
	float step = (square_side_end - square_side_begin)/ (number_of_sections-1);
	float x = square_side_begin;
	for (int i = 0; i < number_of_sections; ++i)
	{
		float y = square_side_end;
		for (int j = 0; j < number_of_sections; ++j)
		{
			coordinates[i][j][0] = calculateX(x,y);
			coordinates[i][j][1] = calculateY(x,y);
			coordinates[i][j][2] = calculateZ(x,y);
			y += step;
		}
		x += step;
	}
	MoveImageDown();
}

// Funkcja ustalaj�ca stan renderowania



void MyInit(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc�cy (wype�nienia okna) ustawiono na czarny
	CreateNet(0.0f, 1.0f);
	FillTableOfColors();
}

/*************************************************************************************/

// Funkcja ma za zadanie utrzymanie sta�ych proporcji rysowanych 
// w przypadku zmiany rozmiar�w okna.
// Parametry vertical i horizontal (wysoko�� i szeroko�� okna) s� 
// przekazywane do funkcji za ka�dym razem gdy zmieni si� rozmiar okna.



void ChangeSize(GLsizei horizontal, GLsizei vertical)
{

	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okre�laj�cej proporcj�
	// wymiar�w okna 
	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;
	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielko�ciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical)  
	glMatrixMode(GL_PROJECTION);
	// Prze��czenie macierzy bie��cej na macierz projekcji 
	glLoadIdentity();
	// Czyszcznie macierzy bie��cej            
	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wsp�czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okre�lenie tak zwanej
	// przestrzeni ograniczaj�cej pozwalaj�cej zachowa� w�a�ciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj�cej s�u�y funkcja
	// glOrtho(...)            
	if (horizontal <= vertical)

		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
	else

		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);
	// Prze��czenie macierzy bie��cej na macierz widoku modelu                                   

	glLoadIdentity();
	// Czyszcenie macierzy bie��cej
}

void keys(unsigned char key, int x, int y)
{
	if (key == 'p') model = 1;
	if (key == 'w') model = 2;
	if (key == 's') model = 3;

	RenderScene(); // przerysowanie obrazu sceny
}

/*************************************************************************************/

// G��wny punkt wej�cia programu. Program dzia�a w trybie konsoli

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(300, 300);

	glutCreateWindow("Uk�ad wsp�rz�dnych 3-D");

	glutDisplayFunc(RenderScene);
	// Okre�lenie, �e funkcja RenderScene b�dzie funkcj� zwrotn�
	// (callback function).  Bedzie ona wywo�ywana za ka�dym razem 
	// gdy zajdzie potrzba przeryswania okna 
	glutReshapeFunc(ChangeSize);
	// Dla aktualnego okna ustala funkcj� zwrotn� odpowiedzialn�
	// zazmiany rozmiaru okna      
	MyInit();
	// Funkcja MyInit() (zdefiniowana powy�ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst�pieniem do renderowania
	glEnable(GL_DEPTH_TEST);
	// W��czenie mechanizmu usuwania powierzchni niewidocznych

	glutKeyboardFunc(keys);

	glutIdleFunc(SpinEgg);

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT
}

/*************************************************************************************/