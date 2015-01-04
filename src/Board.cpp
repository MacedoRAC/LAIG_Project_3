#include "Board.h"


Board::Board(void)
{
}

void Board::drawCylinders() //draw do que esta no anf - passar para aqui
{
	cylinder based(0.3,0.3,0.99,10,10);
	glPushMatrix();
	glTranslated(2.5,0,3.5);
	glRotated(-90,1,0,0);
	based.draw();


	glPopMatrix();
}

void Board::draw()
{
	float x,y,z;
	y = 1;
	x = 0;
	z = 0;

	for(int j = 0; j < 5; j++)
	{
		glPushMatrix();
		glLoadName(j);

		for(int i = 0; i < 7;i++)
		{	
			glPushMatrix();
			glPushName(i);
			if(i == 0  || i == 6 || j == 0 || j == 4)
			{
				y = 0;
				glBegin(GL_QUADS);
				glNormal3f(0,-1,0); 
				glVertex3f(x,y,z);
				glVertex3f(x+1,y,z);
				glVertex3f(x+1,y,z+1);
				glVertex3f(x,y,z+1);
				glEnd();			

				glBegin(GL_QUADS);
				glNormal3f(0,1,0); 
				glVertex3f(x,y,z+1);
				glVertex3f(x+1,y,z+1);			
				glVertex3f(x+1,y,z);			
				glVertex3f(x,y,z);
				glEnd();


			}
			else
			{
				y = 1;
				glBegin(GL_QUADS);
				glNormal3f(0,-1,0); 
				glVertex3f(x,y,z);


				glVertex3f(x+1,y,z);


				glVertex3f(x+1,y,z+1);


				glVertex3f(x,y,z+1);
				glEnd();			

				glBegin(GL_QUADS);
				glNormal3f(0,1,0); 


				glVertex3f(x,y,z+1);

				glVertex3f(x+1,y,z+1);			
				glVertex3f(x+1,y,z);			
				glVertex3f(x,y,z);
				glEnd();

			}

			z++;

			glPopName();
			glPopMatrix();
		}

		z = 0;
		x++;
		glPopMatrix();
	}


	drawCylinders();


}

void Board::draw(Texture *t)
{
	float width = t->getTexLengthS(), height = t->getTexLengthT(), lengthT = 5,heightT = 7;
	float tX,tY,incTX,incTY;

	incTX = width/lengthT;
	incTY = height/heightT;

	tX = 0; 
	tY =0;

	float x,y,z;
	y = 1;
	x = 0;
	z = 0;
	for(int j = 0; j < 5;j++)
	{
		glPushMatrix();
		glLoadName(j);
		for(int i = 0; i < 7;i++)
		{
			glPushMatrix();
			glPushName(i);
			if(i == 0  || i == 6 || j == 0 || j == 4)
			{
				y = 0;
				glBegin(GL_QUADS);
				glNormal3f(0,-1,0); 
				glVertex3f(x,y,z);


				glVertex3f(x+1,y,z);


				glVertex3f(x+1,y,z+1);


				glVertex3f(x,y,z+1);
				glEnd();			

				glBegin(GL_QUADS);

				glNormal3f(0,1,0); 

				glTexCoord2f(tX,tY+incTY); 
				glVertex3f(x,y,z+1);

				glTexCoord2f(tX+incTX,tY+incTY); 
				glVertex3f(x+1,y,z+1);

				glTexCoord2f(tX+incTX,tY); 
				glVertex3f(x+1,y,z);	

				glTexCoord2f(tX,tY); 
				glVertex3f(x,y,z);
				glEnd();


			}
			else
			{
				y = 1;
				glBegin(GL_QUADS);
				glNormal3f(0,-1,0); 
				glVertex3f(x,y,z);


				glVertex3f(x+1,y,z);


				glVertex3f(x+1,y,z+1);


				glVertex3f(x,y,z+1);
				glEnd();			

				glBegin(GL_QUADS);
				glNormal3f(0,1,0); 


				glTexCoord2f(tX,tY+incTY); 
				glVertex3f(x,y,z+1);


				glTexCoord2f(tX+incTX,tY+incTY); 
				glVertex3f(x+1,y,z+1);			

				glTexCoord2f(tX+incTX,tY); 
				glVertex3f(x+1,y,z);	


				glTexCoord2f(tX,tY); 
				glVertex3f(x,y,z);
				glEnd();

			}

			z++;
			tY += incTY;
			glPopName();
			glPopMatrix();
		}
		tY = 0;
		tX+= incTX;
		z = 0;
		x++;	
		glPopMatrix();
	}
	drawCylinders();
}

Board:: ~Board(void)
{
}