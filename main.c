/* DIRETTIVE AL PREPROCESSORE */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

/* DEFINIZIONE DEI TIPI */

typedef struct record_t

{
	char	*cognome;
	char	*nome;
	int		*codice;
	char	*data;
	int		*stipendio;
	char	*categoria;

} record_t;


/* DICHIARAZIONE DELLE FUNZIONI */

int	acquisire_dati(record_t *);
int	inserimento_dati(record_t *);
int	cancellazione_dati(record_t *);
int	trova_elemento(record_t *,int elem);
int	ordinamento();
int	random();
int	pausa();

/* DEFINIZIONE DELLE FUNZIONI (tra cui main) */

int main(void)
{
	int			elem = 0;
	int 		azione = 0;
	int			c;
	record_t	*persona;
	

	/*Inizializzo il vettore di strutture "persona" e invoco la funzione di acquisizione
	  in modo da ottenere i dati dal file se sono presenti,
	  altrimenti si procederà all'aggiunta mediante la funzione "inserimento_dati" */

	persona = (record_t *)malloc(1000 * (sizeof(record_t)));

	printf ("\n #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n");
	printf (" *#*#*#*#*#*#*#                 #*#*#*#*#*#*#*\n");
	printf (" #*             LISTA PERSONALE             *#\n");
	printf (" #*#*#*#*#*#*#*                 *#*#*#*#*#*#*#\n");
	printf (" *#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*\n\n");
		
		
	acquisire_dati(persona);
		
	
	do
	{	/*Interfaccia utente*/	    	
		printf ("\n\n"); 
		printf (" 1) AGGIUNGI PERSONE\n\n");
		printf (" 2) RIMUOVI PERSONA\n\n");
		printf (" 3) RICERCA PERSONE\n\n");
		printf (" 4) RICERCA i-esimo STIPENDIO\n\n");
		printf (" 5) GENERA DATI\n\n");
		printf (" 0) ESCI\n\n");

		do
		{
			printf("\n\n- Selezionare la funzione da eseguire > ");

			c = (scanf("%d", &azione));


			if ((c == 0) || (azione > 5))
			{
				
				if ((scanf("%*[^\n]"))==0)
				
					printf("Azione non valida.\n");
				
			}
		}

		while(c == 0);

	
			switch(azione)
			{								
				case 1: inserimento_dati(persona);
					acquisire_dati(persona);
			
					break;
	
				case 2: cancellazione_dati(persona);
					acquisire_dati(persona);

					break;

				case 3:	trova_elemento(persona, elem);
					acquisire_dati(persona);

					break;

				case 4: ordinamento();
					acquisire_dati(persona);

					break;

				case 5: random();
					acquisire_dati(persona);
					
					break;

					
				case 0: 
					break;

				default: 
					break;
			}
		
	}
	
	while(azione != (0));

	printf ("\n\nGrazie per aver utilizzato questo programma!\n\n");
	printf ("--------------------------------------\n");
	printf ("--------------------------------------\n");
	printf (" Programma creato da\n");
	printf (" Angelo Sasso        \n");
	printf (" a.sasso4@campus.uniurb.it\n");
	printf (" PROGETTO ALGORITMI E STRUTTURE DATI\n");
	printf ("--------------------------------------\n");
	printf ("--------------------------------------\n\n");
		
	return (0);	
}


/*Funzione per acquisizione e stampa dei dati*/

int acquisire_dati(record_t *persona)

{
	FILE		*file;
	int			i;

	clock_t		inizio = 0;
	clock_t		fine;

	/*Dichiaro e inizializzo il contatore "i" a 0*/

	i = 0;
		
	/*Controllo la presenza del file di testo e dei relativi dati all'interno*/

	file = fopen("persone.txt", "r");

	if (file == NULL)
	{
		printf("\nVerificare che il file 'persone.txt' sia contenuto\n");
		printf("nella stessa cartella del file eseguibile\n\n");	

		exit(1);		
	}

	else												/* O(1+(n-1*(30+30+1+30+1+30+20)))+ */
	{	/* Alloco l'array di strutture "persona"
		   inizializzandolo con una dimensione abbastanza elevata per poi riallocarlo 
		   dentro il ciclo for in modo da avere sempre la dimensione esatta dell'array 
		   e dei campi all'interno di ogni struttura */
			

		persona = (record_t *)malloc(10000 * (sizeof(record_t)));

	     	/*Procedo con un ciclo for per la lettura dei dati da file.
         	  Si alloca abbastanza spazio per la struttura e per ogni suo campo,
	          per poi proseguire con 4 acquisizioni di stringhe e 1 acquisizione di int,
	       	  per ogni campo  fino ad arrivare alla fine del file.*/						

		inizio = clock();

		for(i = 0; (!feof(file)) ; i++)			
		{					
			persona				= realloc(persona, sizeof(record_t)*(i+1)); 
			persona[i].cognome		= (char *)malloc(30 * (sizeof(char))); 
			persona[i].nome			= (char *)malloc(30 * (sizeof(char)));
			persona[i].codice      		= (int  *)malloc( 1 * (sizeof(int )));
			persona[i].data			= (char *)malloc(30 * (sizeof(char)));
			persona[i].stipendio		= (int  *)malloc( 1 * (sizeof(int )));
			persona[i].categoria		= (char *)malloc(30 * (sizeof(char)));
				          											      
			if (fscanf(file, "%s", persona[i].cognome) != EOF)
			{
				persona[i].cognome = 
				realloc(persona[i].cognome, sizeof((strlen(persona[i].cognome))));

				printf("%-15s", persona[i].cognome);
			}
		
			if (fscanf(file, "%s", persona[i].nome) != EOF)
			{
				persona[i].nome = 
				realloc(persona[i].nome, sizeof((strlen(persona[i].nome))));

				printf("%-10s\t", persona[i].nome);
			}
							
			if (fscanf(file, "%d", persona[i].codice) != EOF)
			{
				 
				printf("%d\t", *persona[i].codice);
			}
			
			if (fscanf(file, "%s", persona[i].data) != EOF)
			{
				persona[i].data = 
				realloc(persona[i].data, sizeof((strlen(persona[i].data))));

				printf("%-10s\t", persona[i].data);
			}

			if (fscanf(file, "%d", persona[i].stipendio) != EOF)
			{
				printf("%d\t", *persona[i].stipendio);
			}

			if (fscanf(file, "%s", persona[i].categoria) != EOF)
			{
				persona[i].categoria =
				realloc(persona[i].categoria, sizeof((strlen(persona[i].data))));

				printf("%-10s\n", persona[i].categoria);
			}							
		}

		fine = clock();

		printf("\nTempo necessario per l'acquisizione dei record: %f\n", (double)(fine - inizio) / CLOCKS_PER_SEC);
		printf("\n\tPremere INVIO per contniuare >\n");

		getchar();



	
	}				
	
	fclose(file);													/* O(1)+ */
		
	return(0);													/* O(1) */
}

/*Funzione per l'aggiunta di dati*/

int inserimento_dati(record_t *persona)

{

	FILE		*file;
	int 		k;
	int		i;

	clock_t		inizio = 0;
	clock_t		fine;
			
			
	printf (" #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n");
	printf (" #*                LISTA PERSONE            *#\n");
	printf (" #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n");
	printf (" #*               AGGIUNGI PERSONE          *#\n");
	printf (" #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n\n");
	printf ("\n- Inserire il numero delle persone che si desidera registrare >\t");

	file = fopen("persone.txt", "a");
		
	/*Il file "persone.txt" viene aperto in append mode, 
	  si cicla la richiesta all'utente dei dati delle nuove macchine 
	  e si salvano accodandoli a quelli già presenti nel file*/

	if ((scanf("%d", &k ) != 1))
	{
		/*Si procede allo svuotamento del buffer*/

		if(scanf("%*[^\n]") == 0)
					
			printf("\n\nAzione non consentita!\n\n");					
	}

	else
	{
		inizio = clock();
		
		for(i = 0; (i < k) ; i++)										
		{
			persona				= realloc(persona, sizeof(record_t)*(i+1));	
			persona[i].cognome		= (char *)malloc(30 * (sizeof(char))); 
			persona[i].nome			= (char *)malloc(30 * (sizeof(char)));
			persona[i].codice      		= (int  *)malloc( 1 * (sizeof(int )));
			persona[i].data			= (char *)malloc(30 * (sizeof(char)));
			persona[i].stipendio		= (int  *)malloc( 1 * (sizeof(int )));
			persona[i].categoria 		= (char *)malloc(30 * (sizeof(char)));
			
			printf("Digitare COGNOME, NOME, CODICE IDENTIFICATIVO, DATA ASSUNZIONE, STIPENDIO e CATEGORIA\n");
			printf("della nuova persona separati da tabulazione o da spazio: \n\n");
	
			if (scanf("%s", persona[i].cognome) != EOF)
			{
				persona[i].cognome = 
				realloc(persona[i].cognome, sizeof((strlen(persona[i].cognome))));
	
				fprintf(file, "%s\t", persona[i].cognome);
			}
	
			if (scanf("%s", persona[i].nome) != EOF)
			{
				persona[i].nome = 
				realloc(persona[i].nome, sizeof((strlen(persona[i].nome))));
	
				fprintf(file, "%s\t", persona[i].nome);
			}
	
			if (scanf("%d", persona[i].codice) != EOF)
			{
										
				fprintf(file, "%d\t", *persona[i].codice);
			}
	
			if (scanf("%s", persona[i].data) != EOF)
			{
				persona[i].data = 
				realloc(persona[i].data, sizeof((strlen(persona[i].data))));
		
				fprintf(file, "%s\t", persona[i].data);
			}
	
			if (scanf("%d", persona[i].stipendio) != EOF)
			{
				fprintf(file, "%d\t", *persona[i].stipendio);
			}

			if (scanf("%s", persona[i].categoria) != EOF)
			{
				persona[i].categoria =
				realloc(persona[i].categoria, sizeof((strlen(persona[i].categoria))));

				fprintf(file, "%s\n", persona[i].categoria);
			}
											
		}

		fine = clock();

		printf("\nTempo necessario per la creazione dei record: %f\n", (double)(fine - inizio) / CLOCKS_PER_SEC);


		printf("\nRefresh elenco\n\n");											/* O(1)+ */
			
	}	
		
	fclose(file);														/* O(1)+ */

	return(0);														/* O(1) */
}

/*Funzione per la rimozione dei dati*/

int cancellazione_dati(record_t *persona)

{
	int		c;
	int		i = 0;
	int		j = 0;
	int		k = 0;
	FILE		*file;

	clock_t		inizio = 0;
	clock_t		fine;



	printf (" #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n"); 						/* O(1)+ */
	printf (" #*                 LISTA PERSONE           *#\n"); 						/* O(1)+ */
	printf (" #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n"); 						/* O(1)+ */
	printf (" #*                RIMUOVI RECORD           *#\n");						/* O(1)+ */
	printf (" #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n\n");						/* O(1)+ */

	file = fopen("persone.txt", "r");													/* O(1)+ */

	persona = (record_t *)malloc(10000 * (sizeof(record_t)));						/* O(1)+ */
						
	/*In questo caso si procede con un'acquisizione da file 
	  seguita da una stampa numerata 
	  in modo da facilitare la scelta all'utente*/		
				
	for(i = 0; (!feof(file)) ; i++) 																											/* O(n-1)+(30+30+30+1+30+1+30+20))+ */
	{			
					
		persona				= realloc(persona, sizeof(record_t)*(i+1));
		persona[i].cognome		= (char *)malloc(30 * (sizeof(char))); 
		persona[i].nome			= (char *)malloc(30 * (sizeof(char)));
		persona[i].codice      		= (int  *)malloc( 1 * (sizeof(int )));
		persona[i].data			= (char *)malloc(30 * (sizeof(char)));
		persona[i].stipendio		= (int  *)malloc( 1 * (sizeof(int )));
		persona[i].categoria		= (char *)malloc(30 * (sizeof(char)));

		if (fscanf(file, "%s", persona[i].cognome) != EOF)
		{
			persona[i].cognome = 
			realloc(persona[i].cognome, sizeof((strlen(persona[i].cognome))));

			printf("%d\t%-15s", (i+1), persona[i].cognome);
		}
				
		if (fscanf(file, "%s", persona[i].nome) != EOF)
		{
			persona[i].nome = 
			realloc(persona[i].nome, sizeof((strlen(persona[i].nome))));

			printf("%-10s\t", persona[i].nome);
		}
							
		if (fscanf(file, "%d", persona[i].codice) != EOF)
		{
				
			printf("%d\t", *persona[i].codice);
		}

		if (fscanf(file, "%s", persona[i].data) != EOF)
		{
			persona[i].data = 
			realloc(persona[i].data, sizeof((strlen(persona[i].data))));

			printf("%-10s\t", persona[i].data);
		}

		if (fscanf(file, "%d", persona[i].stipendio) != EOF)
		{
			printf("%-d\t", *persona[i].stipendio);
		}

		if (fscanf(file, "%s", persona[i].categoria) != EOF)
		{
			persona[i].categoria =
			realloc(persona[i].categoria, sizeof((strlen(persona[i].categoria))));

			printf("%-10s\n", persona[i].categoria);
		}
								
	}		
			
	fclose(file); 													/* O(1)+ */
		
	/*Ora che i dati sono "indicizzati" si procede a liberare il puntatore per ogni campo
	  della struttura scelta e...*/
		
	do 														/* O(n+(4)) */
	{
		printf("\n\n- Selezionare il numero del record da eliminare > ");

		c = (scanf("%d", &k));

		if (c == 0) 
		{
				
			if ((scanf("%*[^\n]"))==0)
			
			printf("Azione non valida.\n");
				
		}
	}	

				
	while((c == 0) || k <= 0); 

	inizio = clock();											/* O(n*15)+ */
	
	k = k - 1;

		free(persona[k].cognome);
		persona[k].cognome = NULL;

		free(persona[k].nome);
		persona[k].nome = NULL;

		free(persona[k].codice);
		persona[k].codice = NULL;

		free(persona[k].data);
		persona[k].data = NULL;

		free(persona[k].stipendio);
		persona[k].stipendio = NULL;

		free(persona[k].categoria);
		persona[k].categoria = NULL;

		/*...a stampare sul file di testo tutti i dati meno quello scelto dall'utente*/

		file = fopen("persone.txt", "w");

		for (j = 0 ; (j < (i - 1)); j++) 									/* O(n*(5+7) */
		{
			if (j == k);

			else
			{		
				fprintf(file, "%-15s", 		persona[j].cognome);
				fprintf(file, "%-10s\t",	persona[j].nome);
				fprintf(file, "%d\t", 		*persona[j].codice);
				fprintf(file, "%-10s\t", 	persona[j].data);
				fprintf(file, "%d\t", 		*persona[j].stipendio);
				fprintf(file, "%-10s\n", 	persona[j].categoria);
			}
		}

	fclose(file); 

	fine = clock();		

	printf("\nTempo necessario per la rimozione del record: %f\n", (double)(fine - inizio) / CLOCKS_PER_SEC);
											/* O(1+1+1) */

	pausa();									/* O(4) */

	printf("\n\nRefresh elenco\n\n");

	return(0);
}	


int trova_elemento(record_t *persona,int elem)
{
	int	i;
	int	k;
	int	trovato = 0; 																									/* O(1)+ */
	
	FILE	*file;

	clock_t		inizio = 0; 												
	clock_t		fine;


	/* Acquisizione dati*/

	file = fopen("persone.txt", "r"); 																					/* O(1)+ */

	persona = (record_t *)malloc(10000 * (sizeof(record_t))); 															/* O(1)+ */
										
	for(i = 0; (!feof(file)) ; i++)																						/* O(n*(30+30+1+30+1+30+1))+ */		
	{						
		persona				= realloc(persona, sizeof(record_t)*(i+1));
		persona[i].cognome		= (char *)malloc(30 * (sizeof(char))); 
		persona[i].nome			= (char *)malloc(30 * (sizeof(char)));
		persona[i].codice      		= (int  *)malloc( 1 * (sizeof(int )));
		persona[i].data			= (char *)malloc(30 * (sizeof(char)));
		persona[i].stipendio		= (int  *)malloc( 1 * (sizeof(int )));
		persona[i].categoria		= (char *)malloc(30 * (sizeof(char)));

		if (fscanf(file, "%s", persona[i].cognome) != EOF)
		{
			persona[i].cognome = 
			realloc(persona[i].cognome, sizeof((strlen(persona[i].cognome))));
		}
				
		if (fscanf(file, "%s", persona[i].nome) != EOF)
		{
			persona[i].nome = 
			realloc(persona[i].nome, sizeof((strlen(persona[i].nome))));
		}
							
		if (fscanf(file, "%d", persona[i].codice) != EOF)
		{
		}

		if (fscanf(file, "%s", persona[i].data) != EOF)
		{
			persona[i].data = 
			realloc(persona[i].data, sizeof((strlen(persona[i].data))));
		}

		if (fscanf(file, "%d", persona[i].stipendio) != EOF)
		{
		}

		if (fscanf(file, "%s", persona[i].categoria) != EOF)
		{
			persona[i].categoria =
			realloc(persona[i].categoria, sizeof((strlen(persona[i].categoria))));
		}
	}

	fclose(file);													/* O(1)+ */

	i = i - 1;	/*numero degli elementi */ 									/* O(1)+ */


	printf (" #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n");							/* O(5)+ */
  	printf (" #*                 LISTA PERSONE           *#\n");
  	printf (" #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n");							
  	printf (" #*                RICERCA PERSONE          *#\n");
  	printf (" #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n\n");	
			

	k = i-1; 													/* O(1)+ */

	printf("\nInserire il CODICE IDENTIFICATIVO da cercare: >\t");							/* O(1)+ */

	if ((scanf("%d", &elem ) != 1))											/* O(1+2)+ */
	{
		/*Si procede allo svuotamento del buffer*/

		if(scanf("%*[^\n]") == 0)
					
		printf("\n\nAzione non consentita!\n\n");					
	}

	inizio = clock();												/* O(1)+ */

	for(k=0; k<i; k++)                                                                                              /* O(n-1*(1+9))+ */ 
 				
	if(*persona[k].codice == elem)
 	{
  		trovato++;
  		printf("\nIl CODICE IDENTIFICATIVO cercato '%d' si trova in posizione %d\n",elem,k+1);
		printf("\nQuesto è il record relativo:\n\n"); 
		printf("%s\t", persona[k].cognome);
		printf("%s\t", persona[k].nome);
		printf("%d\t", *persona[k].codice);
		printf("%s\t", persona[k].data);
		printf("%d\t", *persona[k].stipendio);
		printf("%s\n", persona[k].categoria);
	 }

	if(trovato==0) 													/* O(4)+ */
  				
	printf("\nIl CODICE IDENTIFICATIVO '%d' non esiste nell'array\n",elem);

	fine = clock();

	printf("\nTempo necessario per confrontare i CODICI IDENTIFICATIVI : %f\n", (double)(fine - inizio) / CLOCKS_PER_SEC);
	

	pausa();													/* O(4) */
			
	return (0);

 															/* COMPLESSITÀ O(n) */
}


int pausa() /* O(4) */
{
 printf ("\n\nPremere <INVIO> per continuare...\n\n");
 getchar();
 getchar();
 return 0;
}	



int random()
{
	int		elem;
	int		i = 0;
	int		j = 0;
	int		k = 0;
	int		l = 0;
	int		t = 0;
	int		num;
	FILE		*file;

	clock_t		inizio = 0;
	clock_t		fine;

	printf("\n- Digitare il numero di elementi che si desidera generare >\t");


	if ((scanf("%d", &elem ) == (0)))
	{			
		printf("Azione non consentita!\n");					
	}
	
	else
	{
		file = fopen("persone.txt", "a");

		inizio = clock();
		
		for(k = 0; k < elem; k++)
		{
				 	
			for(j = 0; j < 2; j++)
			{
		
				for(i = 0; i < 8 ; i++)
				{
					fprintf(file, "%c", ('a'+rand()%('z'-'a')));

				}
			
				fprintf(file,"\t");

			}

			num = rand()%1000000;
			fprintf(file, "%d\t", ('1'+rand()%( num)));

			for(l = 0; l < 8 ; l++)
			{
				fprintf(file, "%c", ('a'+rand()%('z'-'a')));

			}
			
			fprintf(file,"\t");

			num = rand()%1000000;
			fprintf(file, "%d\t", ('1'+rand()%( num)));

			for(t = 0; t < 8 ; t++)
			{
				fprintf(file, "%c", ('a'+rand()%('z'-'a')));

			}
			
			fprintf(file,"\t");




			fprintf(file,"\n");


		}



	fine = clock();

	printf("\nTempo necessario per generare i RECORD : %-10f\n", (double)(fine - inizio) / CLOCKS_PER_SEC);

	
	fclose(file);

	pausa();
	}							
																
	return 0;
}



int ordinamento()
{

	record_t	*persona;
	FILE		*file;
	int		i;
	int		j;
	int		k = 0;
	char		*tmp1 = '\0';
	char		*tmp2 = '\0';
	int		tmp3;
	char		*tmp4 = '\0';
	int		tmp5;
	char		*tmp6 = '\0';
	int		n = 0;

	clock_t		inizio = 0;
	clock_t		fine;



	/* Acquisizione dati */

	file = fopen("persone.txt", "r");

	persona = (record_t *)malloc(10000 * (sizeof(record_t)));
										
	for(i = 0; (!feof(file)) ; i++)			
	{						
		persona				= realloc(persona, sizeof(record_t)*(i+1));
		persona[i].cognome		= (char *)malloc(30 * (sizeof(char))); 
		persona[i].nome			= (char *)malloc(30 * (sizeof(char)));
		persona[i].codice      		= (int  *)malloc( 1 * (sizeof(int )));
		persona[i].data			= (char *)malloc(30 * (sizeof(char)));
		persona[i].stipendio		= (int  *)malloc( 1 * (sizeof(int )));
		persona[i].categoria		= (char *)malloc(30 * (sizeof(char)));

		if (fscanf(file, "%s", persona[i].cognome) != EOF)
		{
			persona[i].cognome = 
			realloc(persona[i].cognome, sizeof((strlen(persona[i].cognome))));
		}
				
		if (fscanf(file, "%s", persona[i].nome) != EOF)
		{
			persona[i].nome = 
			realloc(persona[i].nome, sizeof((strlen(persona[i].nome))));
		}
							
		if (fscanf(file, "%d", persona[i].codice) != EOF)
		{
		}

		if (fscanf(file, "%s", persona[i].data) != EOF)
		{
			persona[i].data = 
			realloc(persona[i].data, sizeof((strlen(persona[i].data))));
		}

		if (fscanf(file, "%d", persona[i].stipendio) != EOF)
		{
		}

		if (fscanf(file, "%s", persona[i].categoria) != EOF)
		{
			persona[i].categoria =
			realloc(persona[i].categoria, sizeof((strlen(persona[i].categoria))));
		}
	}

	fclose(file);

	i = i - 1;	


	printf (" #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n");
  	printf (" #*                 LISTA PERSONE           *#\n");
  	printf (" #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n");
  	printf (" #*          RICERCA i-esimo STIPENDIO      *#\n");
  	printf (" #*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#\n\n");	

	printf("\nInserire un intero 'i' >\t");

	if (scanf("%d", &n) == 0)
					
	printf("\nInserire un intero.\n");

		else

		inizio = clock();      								/* O(1)+ */
				
		j = 0;										/* O(1)+ */
								
		for (j = 1; j < i; j++)                                                         /* O((n-1)+3+6)+ */
		{
			tmp1 = persona[j].cognome;
			tmp2 = persona[j].nome;
			tmp3 = *persona[j].codice;
			tmp4 = persona[j].data;
			tmp5 = *persona[j].stipendio;
			tmp6 = persona[j].categoria;

			k = j - 1;								/* O(1)+ */

			while(k >= 0 && (*persona[k].stipendio > tmp5) )			/* O((n-1)+2+7)+O(8)+O(4) */
			{
				persona[k+1].cognome		= persona[k].cognome;
				persona[k+1].nome 		= persona[k].nome;
				*persona[k+1].codice 		= *persona[k].codice;
				persona[k+1].data 		= persona[k].data;
				*persona[k+1].stipendio		= *persona[k].stipendio;
				persona[k+1].categoria		= persona[k].categoria;
					
				k--;									
			}

			
				
			persona[k+1].cognome		= tmp1;
			persona[k+1].nome		= tmp2;
			*persona[k+1].codice		= tmp3;
			persona[k+1].data		= tmp4;
			*persona[k+1].stipendio 	= tmp5;
			persona[k+1].categoria		= tmp6;
		}
		
		fine = clock();

		printf("\nTempo necessario a riordinare la struttura per STIPENDIO : %f\n\n", (double)(fine - inizio) / CLOCKS_PER_SEC);
				

				
			
		if (k+n <= i)										/* O(n*(7))+O(3) */
		{	
			printf("\nIl record relativo al '%d' elemento per stipendio è:\n\n", n);
			printf("%d)\t%s\t", n,		persona[n-1].cognome);
			printf("%s\t", 			persona[n-1].nome);
			printf("%d\t", 			*persona[n-1].codice);
			printf("%s\t", 			persona[n-1].data);
			printf("%d\t", 			*persona[n-1].stipendio);
			printf("%s\n\n", 		persona[n-1].categoria);
		}

		else
			printf("\nNon esiste il record numero '%d'.\n\n\n", n);	

			pausa();	
	return 0;
}
