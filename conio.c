#include "conio.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

/*
 * Obtiene un caracter del teclado sin imprimirlo a pantalla.
 * Podemos hacer un casting a int para ver qué tecla ha sido pulsada en el mapa de teclado.
 */
char getch(void) {
	struct termios t;
	char c;

	/* Obtenemos la configuración actual de la terminal */
	tcgetattr(0, &t);

	/* Le apagamos los bits de "ICANON" y "ECHO" con el operador AND */
	t.c_lflag &= ~ICANON;
	t.c_lflag &= ~ECHO;

	/* Establecemos la nueva configuración de la terminal */
	tcsetattr(0, TCSANOW, &t);

	setbuf(stdin, NULL);
	c = getchar();
	setbuf(stdin, NULL);
	setbuf(stdout, NULL);

	/* ¡Ojo! ¡Si no dejamos todo como estaba le dejaremos
	 * al usuario la terminal rota!
	 */
	t.c_lflag |= ICANON;
	t.c_lflag |= ECHO;
	tcsetattr(0, TCSANOW, &t);
	return c;
}
