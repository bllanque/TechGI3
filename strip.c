#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "strip.h"

char* strip(char* str)
{
	char* pos = str;												// Anfangsposition eines ersten '/'
	char* sub = NULL;												// Folgeposition eines nächsten '/'
	
	char* tmp = NULL;												// Temporärspeicher (für Verschiebungen)
	
	printf("DEBUG: durchsuche %s\n\n", str);
	
	while (pos != 0) {												// Wiederhole, solange '/' folgen:
		if ((pos = strchr(pos, '/'))) {								// falls (noch eine) mögliche Folge von '/' ex.,
			sub = pos;												// dessen Anfangsposition merken
	
			printf("DEBUG: erster (lokaler) slash ab %s\n", pos);
			
			while (strchr(sub, '/') == sub) {						// falls direkt im Anschluss (eine Folge von) '/' ex.,
				sub++;												// lokal weitersuchen
			}
	
			printf("DEBUG: letzter (lokaler) slash vor %s\n", sub);
			
			if (sub > pos+1) {										// falls mehr als ein '/' hintereinander vorkam...
				printf("DEBUG: entferne %ld mal '/'\n", sub-pos-1);
	
				if ((tmp = malloc(strlen(sub))) == (char*) NULL) {	// Platz für den "Suffix" allokieren
					printf("DEBUG: Fehler beim allokieren von %ld Zeichen. Gebe auf..\n\n", (long) strlen(sub));
					return NULL;
				}
				
				strncpy(tmp, sub, strlen(sub));						// Substring temporär umkopieren
				*(tmp + strlen(sub)) = '\0';						// terminieren nicht vergessen...
				strncpy(pos+1, tmp, strlen(sub));					// temporäre Kopie ans Ziel schreiben
				*(pos+1 + strlen(sub)) = '\0';						// terminieren nicht vergessen...

				printf("DEBUG: extrahierter Rest ist %s\n", tmp);
				printf("DEBUG: neuer Zwischenstand wird %s\n\n", str);

				free(tmp);											// allokierten Platz freigeben

				pos++;												// setze fort hinter erstem '/'
			}
			else {
				pos = sub;											// setze fort hinter *dem* '/'
				printf("DEBUG: einzelnes '/', nichts zu tun\n\n");
			}	
		}
	}
	
	return str;
}


TestResult test_strip()
{
	char str[] = "/usr/////////bin///////////env/tmp///////null/";	//example string
	char* p = strip(str);

	return (strcmp("/usr/bin/env/tmp/null/", p)? NOT_OK : OK);
}
