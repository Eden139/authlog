#include "auth.h"
int count_line(FILE* stream) {
	int count = 0;
	while(fscanf(stream, "%*[^\n]\n") != EOF) count++;
	rewind(stream);
	return count;
}
void write_head(void) {
	printf("Content-type: text/html\n\n");
	printf("<!DOCTYPE html>"
			"<html>"
			"<head>"
				"<meta charset=\"utf-8\"/>"
				"<meta type=\"description\" value=\"Voici le contenu du fichier auth.log\"/>"
				"<title>AUTHLOG</title>"
		);
	write_css();
	printf("</head>");
	return ;
}
void write_css(void) {
	printf("<style>"
			":root {"
				"margin: 0;"
				"padding: 0;"
				"font-size: 16px;"
				"font-family: sans-serif;"
			"}"
			"main {"
				"display: flex;"
				"flex-direction: column;"
				"justify-content: center;"
			"}"
			"table {"
				"margin: 2rem auto;"
				"border: 2px solid darkblue;"
				"border-collapse: collapse;"
				"box-shadow: 0 0 5px rgba(0, 0, 0, 0.7);"
			"}"
			"tr, td, th {"
				"border: 1px solid #ddd;"
			"}"
			"thead {"
				"background: darkblue;"
				"color: white;"
			"}"
			"td, th {"
				"border: 1px solid;"
				"padding: 0.8rem 1.3rem;"
				"text-align: center;"
			"}"
			"th {"
				"text-transform: uppercase;"
				"font-weight: bolder;"
				"font-size: 1.4rem;"
				"letter-spacing: 0.15ch;"
			"}"
			"tr:nth-child(even) {"
				"background: rgba(0,0,0,0.04);"
			"}"
			"p {"
				"text-align: center;"
				"text-transform: uppercase;"
				"font-size: 2rem;"
				"color: red;"
			"}"
			".pagination {"
				"display: flex;"
				"justify-content: center;"
				"width: auto;"
				"font-size: 1.2rem;"
			"}"
			".pagination a {"
				"margin: .3rem;"
				"padding: .7rem;"
				"border: .125rem solid;"
				"color: darkblue;"
				"text-decoration: none;"
			"}"
			".pagination a:hover  {"
				"background: rgba(0, 0, 0, 0.06);"
			"}"
			".pagination a[class=\"blue\"] {"
				"background: darkblue;"
				"padding: 1rem;"
				"color: white;"
			"}"
		"</style>"
	      );
}
void write_body(FILE* auth) {
	int count = count_line(auth), user_number;
	char* str = getenv("QUERY_STRING"), *user = NULL, d[] = "$DEFAULT$", *p = NULL, *test;
	char vide[] = "";
	int page = 1;
	user = d;
	
	if(*str != '\0') {
		test = strstr(str, "user=");
		if(test != NULL) {
			user = test;
			sscanf(user + 5, "%m[^\n&]", &user);
			if(user == NULL) user = vide;
		}
		if((p = strstr(str, "page=")) != NULL) {
			sscanf(p + 5, "%d", &page);
		}
	}
	

	printf("<body>");
	printf("<main>");
		Auth* session = get_users(auth, count, &user_number, user);
		write_table(session, &user_number,  page, user);
	printf("</main>");
	printf("</body>");

}
void write_table(Auth* session, int* user_number, int page, char* user) {
	if(*user_number == 0) {
		printf("<p>Il n'y a pas d'utilisateur de ce nom</p>");
	}
	else {
		printf("<table>");
		printf("<thead>"
				"<tr>"
					"<th>User</th>"
					"<th>session</th>"
					"<th>status</th>"
					"<th>date</th>"
				"<tr>"
			"</thead>"
		      );
		printf("<tbody>");
	/*
		for(int i = 0; i < *user_number; ++i) {

			printf("<tr>"
					"<td>%s</td>"
					"<td>%s</td>"
					"<td>%s</td>"
					"<td>%s</td>"
				"</tr>"
				, session[i].name, session[i].session, session[i].status, session[i].datetime
				);
		}
	*/
		for(int i = (page-1) * 10; i < min(page * 10, *user_number); i++) {
			printf("<tr>"
					"<td>%s</td>"
					"<td>%s</td>"
					"<td>%s</td>"
					"<td>%s</td>"
				"</tr>"
				, session[i].name, session[i].session, session[i].status, session[i].datetime
				);
		}

		printf("</tbody>");
		printf("</table>");
		printf("<nav class=\"pagination\">");
		int first = page - min(4, page - 1);
		int last_page = (int)ceil(*user_number/10.0);
		int last = min(first + 9, last_page);
		for(int i = first; i <= last; i++){
			printf("<a href=\"http://www.authlog.mg/?user=%s&page=%d\"%s>%d</a>", user, i, i == page ? "class=\"blue\"": "", i);
		}
		printf("</nav>");
	}
}
int min(int a, int b) {
	return a < b ? a : b;
}
Auth* get_users(FILE* auth, int count, int* user_number, char* user) {
	Auth* session = malloc(count * sizeof(Auth));
	char* row, *here;
	*user_number = 0;
	if(strcmp(user, "$DEFAULT$") == 0) {
		while(fscanf(auth, "%m[^\n]\n", &row) != EOF){
			if(strstr(row, "for user") != NULL) {
				session[*user_number].datetime = malloc(100);
				sscanf(row, "%s%*s%ms%*s%*s%ms%*s%*s%ms", session[*user_number].datetime, &session[*user_number].session, &session[*user_number].status, &session[*user_number].name);
				strtok(session[*user_number].name, "(");
				strtok(session[*user_number].session, ":([");
				to_gasy(session[*user_number].datetime);
				(*user_number)++;
			}

		}
	}
	else {
		while(fscanf(auth, "%m[^\n]\n", &row) != EOF) {
			if((here = strstr(row, "for user")) != NULL) {
				if(strncasecmp(here + 9, user, strlen(user)) == 0) {
					session[*user_number].datetime = malloc(100);
					sscanf(row, "%ms%*s%ms%*s%*s%ms%*s%*s%ms", &session[*user_number].datetime, &session[*user_number].session, &session[*user_number].status, &session[*user_number].name);
					strtok(session[*user_number].name, "(");
					strtok(session[*user_number].session, ":([");
					to_gasy(session[*user_number].datetime);
					(*user_number)++;
				}
			}
		}
	}
//	free(row);free(here);
	return realloc(session, sizeof(Auth)**user_number);
}
void to_gasy(char* date) {
	int an, mois, jour, heure, minute, seconde;
	sscanf(date, "%d-%d-%dT%d:%d:%d", &an, &mois, &jour, &heure, &minute, &seconde);
	int njours = (an - 1) * 365;
	njours += an > 1582  ? (an - 1) / 4 - (an-1) / 100 + (an - 1) / 400 + 2 : (an - 1) / 4;
	njours += (mois - 1) * 31;
	switch(mois) {
		case 12:
			--njours;
		case 11:
		case 10:
			--njours;
		case 9:
		case 8:
		case 7:
			--njours;
		case 6:
		case 5:
			--njours;
		case 4:
		case 3:
			if(an > 1582) njours -= (an % 4 == 0) && (an % 100 != 0 || an % 400 == 0) ? 2 : 3;
			else njours -= (an % 4 == 0) ? 2: 3;
			break;

	}
	njours += (jour - 1);
	char *gasy[] = {"Sabotsy", "Alahady", "Alatsinainy", "Talata", "Alarobia", "Alakamisy", "Zoma"};
	char *volana[] = {"Janoary", "Febroary", "Martsa", "Aprily", "May", "Jona", "Jolay", "Aogositra", "Septambra", "Oktobra", "Novambra", "Desambra"};
	sprintf(date, "%s %d %s %d - %02d:%02d:%02d", gasy[njours % 7], jour, volana[mois -1], an, heure, minute, seconde);
	return;
}
