#include <GL/glut.h>    // GLUT Library
#include <GL/gl.h>  // OpenGL32 Library
#include <GL/glu.h> // GLu32 Library
#include <stdbool.h>

int window;

/* angle de rotation pour notre carre */
float rcx = 0.0f;
float rcy = 0.0f;


bool buttonIsPressed = false;

int xCamera = 0;
int yCamera = 0;

int xInit = 0;
int yInit = 0;



void mouse(int button,int state,int x,int y)
{
        if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
        {
                buttonIsPressed = true;
                xInit = x;
                yInit = y;
        }
} //détecte qu'un bouton est appuyé

void mousemotion(int x,int y)
{
        if (buttonIsPressed)
        {
                xCamera = (x - xInit)/8;
                yCamera = (y - yInit)/8;

                gluLookAt(xCamera, yCamera, -15.0f,
                          0.0f, 0.0f, 0.0f,
                          0.0f, 1.0f, 0.0f);

                glutPostRedisplay();
        }
} //calcul et applique le déplacement (x et y sont les positions de la souris dans la fenêtre au moment de l'appel de la fonction.)
void keyboard(unsigned char touche,int x,int y)
{
        switch(touche)
        {
        case 'q':
        case 'Q':
        case 27:
                exit(EXIT_SUCCESS);
                break;
        }

        glutPostRedisplay();
}

/* fonction d'initialisation */
void InitGL(int Width, int Height)
{
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Fond noir
        glClearDepth(1.0);  // on vide le z-buffer
        glDepthFunc(GL_LESS); // on définit le type de test
        glEnable(GL_DEPTH_TEST); // on permet les tests en question
        glShadeModel(GL_SMOOTH); // Smooth Color Shading

        glMatrixMode(GL_PROJECTION);            // mode 'projection'
        glLoadIdentity(); // on initialise avec la matrice identité
        gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f); // calcul de l'aspect ratio de la fenêtre

        glMatrixMode(GL_MODELVIEW); // on passe en mode 'vue'
}

/* en cas de redimensionnement */
void ReSizeGLScene(int Width, int Height)
{
        if (Height==0)  // au cas où
                Height=1;

        glViewport(0, 0, Width, Height); // on utilise toute la fenêtre

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f); // aspect ratio
        glMatrixMode(GL_MODELVIEW);
}

/* dessin de la scène */
void DrawGLScene()
{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // on vide les buffers
        glLoadIdentity(); // on initialise avec la matrice identité

        gluLookAt(xCamera, yCamera, -15.0f,
                  0.0f, 0.0f, 0.0f,
                  0.0f, 1.0f, 0.0f);

        //glTranslatef(0.0f,0.0f,-10.0f); // on translate la scène vers le fond

        //glRotatef(rcy,0.0f,1.0f,0.0f); // on fait tourner la scène sur l'axe des Y
        //glRotatef(rcx,1.0f,0.0f,0.0f); // on fait tourner la scène sur l'axe des X

        //on entre les données qui serviront à dessiner un cube

        GLfloat vertices[] = {0.0f, 0.0f, -1.0f,
                              -1.0f, 0.0f, -1.0f,
                              -1.0f, -1.0f, -1.0f,
                              0.0f, -1.0f, -1.0f,
                              0.0f, -1.0f, 0.0f,
                              -1.0f, -1.0f, 0.0f,
                              -1.0f, 0.0f, 0.0f,
                              0.0f, 0.0f, 0.0f};

        GLubyte indices[] = {0, 1, 2, 3,
                             6, 7, 0, 1,
                             4, 5, 6, 7,
                             2, 3, 4, 5,
                             6, 1, 2, 5,
                             7, 0, 3, 4};

        GLfloat colors[] = {1.0f, 0.0f, 0.0f,
                            0.0f, 1.0f, 0.0f,
                            0.0f, 0.0f, 1.0f,
                            1.0f, 1.0f, 1.0f};

        //on écrit les fonctions opengl et la matrice de translation pour
        //déplacer le cube

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        GLfloat m[] =
        {
                1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                -3, -1, 0, 1
        };

        glMultMatrixf(m);

        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glColorPointer(3, GL_FLOAT, 0, colors);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);


        //on écrit les fonctions opengl qui nous servent à dessiner
        //la symétrie du cube par rapport à l'axe yOz

        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPushMatrix();

        GLfloat m1[] =
        {
                -1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
        };


        glMultMatrixf(m1);
        glMultMatrixf(m);

        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glColorPointer(3, GL_FLOAT, 0, colors);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        glPopMatrix();




        //on fait de même pour dessiner un tétrahèdre et sa symétrie

        GLfloat vertices1[] = {0.5f, 0.0f, 0.0f,
                               1.0f, 0.0f, -1.0f,
                               0.0f, 0.0f, -1.0f,
                               0.5f, 0.5f, -0.5f};

        GLubyte indices1[] = {0, 1, 2,
                              0, 1, 3,
                              1, 2, 3,
                              0, 2, 3};

        GLfloat colors1[] = {1.0f, 0.0f, 1.0f,
                             0.0f, 0.0f, 1.0f,
                             1.0f, 0.0f, 1.0f,
                             0.0f, 0.0f, 1.0f,
                             1.0f, 0.0f, 1.0f};


        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();

        GLfloat m2[] =
        {
          1, 0, 0, 0,
          0, 1, 0, 0,
          0, 0, 1, 0,
          3, -1, 0, 1};


        glMultMatrixf(m2);

        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glColorPointer(3, GL_FLOAT, 0, colors1);
        glVertexPointer(3, GL_FLOAT, 0, vertices1);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices1);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);



        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPushMatrix();

        glMultMatrixf(m1);
        glMultMatrixf(m2);

        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glColorPointer(3, GL_FLOAT, 0, colors1);
        glVertexPointer(3, GL_FLOAT, 0, vertices1);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_BYTE, indices1);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        glPopMatrix();


        //glLoadIdentity(); // on ré initialise le point de vue de la scène



        rcx += 0.1f;    // Augmente la variable pour la rotation du carre sur l'axe des x
        rcy += 0.05f;   // Augmente la variable pour la rotation du carre sur l'axe des y

        // on échange les buffers (double buffering)
        glutSwapBuffers();
}



int main(int argc, char **argv)
{
        /* initialisation de glut */
        glutInit(&argc, argv);

        /* Mode d'affichage
           RGBA color
           Double buffer
           Alpha components supported
           z-buffer */
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

        /* taille de la fenêtre 640 x 480 */
        glutInitWindowSize(640, 480);

        /* la fenêtre se positionne en haut à gauche */
        glutInitWindowPosition(0, 0);

        /* on crée la fenêtre */
        window = glutCreateWindow("Fortement inspire par les Tutoriaux NeHe - exo1");

        /* On 'register' la fonction de dessin */
        glutDisplayFunc(&DrawGLScene);

        /* fullscreen */
        /* glutFullScreen(); */

        /* même sans événements, on va re dessiné la scène */
        glutIdleFunc(&DrawGLScene);


        glutKeyboardFunc(&keyboard);
        glutMouseFunc(&mouse);
        glutMotionFunc(&mousemotion);

        /* en cas de redimensionnement */
        glutReshapeFunc(&ReSizeGLScene);


        /* on initialise la scène */
        InitGL(640, 480);

        /* On lance la boucle de la gestion d'événements */
        glutMainLoop();

        return 1;
}
