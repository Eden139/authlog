#include <stdio.h>

void write_css(void);
int main() {
	printf("Content-type: text/html\n\n");
	printf("<!DOCTYPE html>");
	printf("<html>"
			"<head>"
				"<meta charset=\"utf-8\">"
				"<title>Inscription</title>"
		);
	write_css();
	printf("</head>");
	printf("<body>");
	printf("<main>");
	printf("<h2>inscription</h2>");
	printf("<form action=\"verification.cgi\" method=\"get\">"
			"<div class=\"input\">"
				"<input type=\"text\" placeholder=\"Username\" name=\"name\">"
					"<svg xmlns=\"http://www.w3.org/2000/svg\" height=\"1em\" viewBox=\"0 0 448 512\">"
						"<path d=\"M224 256A128 128 0 1 0 224 0a128 128 0 1 0 0 256zm-45.7 48C79.8 304 0 383.8 0 482.3C0 498.7 13.3 512 29.7 512H418.3c16.4 0 29.7-13.3 29.7-29.7C448 383.8 368.2 304 269.7 304H178.3z\"/>"
					"</svg>"
			"</div>"
			"<div class=\"input\">"
				"<input type=\"password\" placeholder=\"Password\" name=\"passwd\">"
					"<svg xmlns=\"http://www.w3.org/2000/svg\" height=\"1em\" viewBox=\"0 0 448 512\">"
						"<path d=\"M144 144v48H304V144c0-44.2-35.8-80-80-80s-80 35.8-80 80zM80 192V144C80 64.5 144.5 0 224 0s144 64.5 144 144v48h16c35.3 0 64 28.7 64 64V448c0 35.3-28.7 64-64 64H64c-35.3 0-64-28.7-64-64V256c0-35.3 28.7-64 64-64H80z\"/>"
					"</svg>"
			"</div>"
			"<div class=\"input\">"
				"<input type=\"password\" placeholder=\"Confirmer le mdp\" name=\"confirm-passwd\">"
					"<svg xmlns=\"http://www.w3.org/2000/svg\" height=\"1em\" viewBox=\"0 0 448 512\">"
						"<path d=\"M144 144v48H304V144c0-44.2-35.8-80-80-80s-80 35.8-80 80zM80 192V144C80 64.5 144.5 0 224 0s144 64.5 144 144v48h16c35.3 0 64 28.7 64 64V448c0 35.3-28.7 64-64 64H64c-35.3 0-64-28.7-64-64V256c0-35.3 28.7-64 64-64H80z\"/>"
					"</svg>"
			"</div>"

			"<button type=\"submit\">Envoyer</button>"
		);
	printf("</main>");

	printf("</body>");
	printf("</html>");


	return 0;
}
void write_css(void) {
	printf("<style>"
		":root {"
			"font-family: sans-serif;"
			"font-size: 40px;"
		"}"
		"* {"
			"padding: 0;"
			"margin: 0;"
		"}"
		"body {"
			"display: flex;"
			"min-height: 100vh;"
			"align-items: center;"
			"justify-content: center;"
		"}"
		"main {"
			"padding: 1rem 2rem 2rem 2rem;"
			"display: flex;"
			"flex-direction: column;"
			"align-items: center;"
			"justify-content: center;"
			"border-radius: .5rem;"
			"border: 2px solid rgba(0, 0, 0, 0.7);"
			"background: rgba(0, 0, 0, .3);"
		"}"
		"main h2 {"
			"text-transform: uppercase;"
			"color: rgba(0, 0, 0, 0.8);"
			"margin-bottom: 1.6rem;"
			"font-size: 1.3rem;"
		"}"
		"form {"
			"width: 100%%;"
			"display: flex;"
			"flex-direction: column;"
			"justify-content: center;"
		"}"
		"form .input {"
			"position: relative;"
			"display: flex;"
			"justify-content: center;"
		"}"
		"form .input svg {"
			"position: absolute;"
			"fill: grey;"
			"right: .9rem;"
			"top: .3rem;"
			"height: .8rem;"
		"}"
		"form .input input {"
			"border: 2px solid rgba(0, 0, 0, 0.7);"
			"outline: none;"
			"width: 85%%;"
			"height: 1.5rem;"
			"margin-bottom: 1.3rem;"
			"border-radius: .3rem;"
			"padding-left: .3rem;"
			"font-size: .5rem;"
		"}"
		"form .input input::placeholder {"
			"font-size: .5rem;"
			"color: rgba(0, 0, 0, 0.7);"
		"}"
		"form button {"
			"width: 85%%;"
			"height: 1.5rem;"
			"border-radius: .3rem;"
			"font-size: .6rem;"
			"margin-left: .7rem;"
			"text-transform: uppercase;"
			"font-weight: 600;"
		"}"

		"</style>"
	      );
}

