#include <stdio.h>
#include <string.h>
#include "strip.h"

char* strip(char* str)
{
	char* pos = str;												// Anfangsposition eines ersten '/'
	char* sub = 0;													// Folgeposition eines nächsten '/'

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
				printf("DEBUG: entferne %ld mal '/'\n\n", sub-pos-1);
	
				// place string manipulation here...	
				
			}
			else {
				printf("DEBUG: einzelnes '/', nichts zu tun\n\n");
				
				// nothing to be done here...
			}
				
			pos = sub;												// setze fort ab aktueller Position...
		}
	}
			
	return str;
}


TestResult test_strip()
{
	char str[] = "/usr//bin///env";	//example string
	char* p = strip(str);
	return (strcmp("/usr/bin/env", p)? NOT_OK : OK);
}

