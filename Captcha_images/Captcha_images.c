/* Tells the compiler not to add padding for these structs. This may
be useful when reading/writing to binary files. */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define BUFF_SIZE 100
#pragma pack(1)

typedef struct _bmp_fileheader
{
	unsigned char  fileMarker1; /* 'B' */
	unsigned char  fileMarker2; /* 'M' */
	unsigned int   bfSize; /* File's size */
	unsigned short unused1;
	unsigned short unused2;
	unsigned int   imageDataOffset; /* Offset to the start of image data */
}bmp_fileheader;

typedef struct _bmp_infoheader
{
	unsigned int   biSize; /* Size of the info header - 40 bytes */
	signed int     width; /* Width of the image */
	signed int     height; /* Height of the image */
	unsigned short planes;
	unsigned short bitPix;
	unsigned int   biCompression;
	unsigned int   biSizeImage; /* Size of the image data */
	int            biXPelsPerMeter;
	int            biYPelsPerMeter;
	unsigned int   biClrUsed;
	unsigned int   biClrImportant;
}bmp_infoheader;

//structura pixel este folosita la matricea de pixeli, un pixel fiind format din 3 valori BGR 
typedef struct _pixel
{
	unsigned char B;
	unsigned char G;
	unsigned char R;
}pixel;

#pragma pack()

//Functia citeste matricea de pixeli 
pixel **LoadBitmapFile(char *filename, bmp_infoheader *bitmapInfoHeader, bmp_fileheader *bitmapFileHeader)
{	
	pixel **bitmapImage;
	int i, j, padding;

	FILE *filePtr;
	filePtr = fopen(filename, "rb");

	if (filePtr == NULL)
		return NULL;

	fread(bitmapFileHeader, sizeof(bmp_fileheader), 1, filePtr);
	fread(bitmapInfoHeader, sizeof(bmp_infoheader), 1, filePtr);
	padding = (4 - (3 * bitmapInfoHeader->width) %4) %4;

	bitmapImage = (pixel**)malloc(bitmapInfoHeader->height * sizeof(pixel*));

	for (i = 0; i < bitmapInfoHeader->height; i++)
		bitmapImage[i] = (pixel*)malloc(bitmapInfoHeader->width * sizeof(pixel));

	for (i = bitmapInfoHeader->height - 1; i >= 0 ; i--)
	{
		for (j = 0; j < bitmapInfoHeader->width; j++)
			fread(&bitmapImage[i][j], sizeof(pixel), 1, filePtr);
		fseek(filePtr, padding * sizeof(unsigned char), SEEK_CUR);
	}
	fclose(filePtr);
	return bitmapImage;
}

//Functia primeste un parametru de tip pixel si verifica daca este alb
int estePixelAlb(pixel p)
{
	if (p.B == 255 && p.G == 255 && p.R == 255)
		return 1;
	return 0;
}

//Functia returneaza 1 daca se  gaseste cifra 1 in matricea de pixeli si -1 daca nu exista
int determinaCifra1(pixel **bitmapImage, int i, int j, int width)
{
	int l, m, totiAlbi = 1;

	for (l = 0; l < 4; l++)
	{
		for (m = 0; m < 5; m++)
		{
			if(!estePixelAlb(bitmapImage[j+m][i+l]))
				totiAlbi = 0;
		}
	}

	if (totiAlbi == 0)
		return -1;

	if (i + 5 < width && !estePixelAlb(bitmapImage[j][i + 5]))
		return -1;

	if (!estePixelAlb(bitmapImage[j][i + 4]) && !estePixelAlb(bitmapImage[j + 1][i + 4]) 
		&& !estePixelAlb(bitmapImage[j + 2][i + 4]) && !estePixelAlb(bitmapImage[j + 3][i + 4])
		&& !estePixelAlb(bitmapImage[j + 4][i + 4]))
		return 1;


	return -1;
}

//functia returneaza 1 daca se gaseste o cifra care trebuie eliminata
int esteCifraDeEliminat(int cifra, int *numere, int counter)
{
	int i;
	for (i = 0; i < counter; i++)
		if (cifra == numere[i])
			return 1;
	return 0;
}

//functia imi muta o cifra din matricea de pixeli  pe o pozitie anterioara , de unde s-a ssters o cifra
void mutaCifra(pixel **bitmapImage, int i_from, int j_from, int i_to, int j_to)
{	
	int l, m;
	for (l = 0; l < 5; l++)
	{	
		for (m = 0; m < 5; m++)
		{
			bitmapImage[i_to + l][j_to + m] = bitmapImage[i_from + l][j_from + m];
		}
	}	

}

// functia  face pixeli albi al cifrelor care s-au mutat spre stanga
void makeWhite(pixel **bitmapImage, int j, int i)
{
	int l, m;

	for (l = 0; l < 5; l++)
	{
		for (m = 0; m < 5; m++)
		{
			bitmapImage[j+m][i+l].B = 255;
			bitmapImage[j+m][i+l].G = 255;
			bitmapImage[j+m][i+l].R = 255;
		}
	}
}

//Functia eliminaCifre foloseste functiile : determinaCifra, determinaCifra1, esteCifradeEliminat, mutaCifre si makeWhite
// si dupa apelarea functiei rezulta imaginea corespodndenta task-ului 3
void eliminaCifre(pixel **bitmapImage, int width, int height, int *linii, int *coloane, int *nrCifre, int *numere, int counter)
{
	int i, j, cifra = -1, l, m, nrDeleted = 0;
	*nrCifre = 0;
	for (i = 0; i < width - 4; i++)
	{
		for (j = 0; j < height - 4; j++)
		{
			if (!estePixelAlb(bitmapImage[j][i]))
			{
				cifra = determinaCifra(bitmapImage, i, j);
			}
			else
			{
				cifra = determinaCifra1(bitmapImage, i, j, width);
			}

			if (cifra != -1)
			{
				linii[*nrCifre] = j;
				coloane[*nrCifre] = i;
				(*nrCifre)++;	
				if (esteCifraDeEliminat(cifra, numere, counter))
				{
					makeWhite(bitmapImage, j, i);
					nrDeleted++;
				}
				else
				{	
					if (nrDeleted != 0)
					{
						mutaCifra(bitmapImage, linii[*nrCifre - 1], coloane[*nrCifre - 1], linii[*nrCifre - 1 - nrDeleted], coloane[*nrCifre - 1- nrDeleted]);
						makeWhite(bitmapImage,linii[*nrCifre - 1], coloane[*nrCifre - 1]);
					}
				}
			}
		}
	}
}

//Functia determinaCifra imi returneaza fiecare  cifra din matricea de pixeli incepand cu  pozitia bitmapImage[j][i] altfel -1
int determinaCifra(pixel **bitmapImage, int i, int j)
{	
	if (j-1 >= 0 && i-1 >= 0)
		if (!estePixelAlb(bitmapImage[j][i-1]) && !estePixelAlb(bitmapImage[j-1][i]))
			return -1;
	if (!estePixelAlb(bitmapImage[j+1][i]) && !estePixelAlb(bitmapImage[j+1][i+4]) &&  !estePixelAlb(bitmapImage[j+3][i])
		&& !estePixelAlb(bitmapImage[j+3][i+4]) && estePixelAlb(bitmapImage[j+2][i+2]) && !estePixelAlb(bitmapImage[j][i+2])
		&& !estePixelAlb(bitmapImage[j][i+2]) && !estePixelAlb(bitmapImage[j+4][i+2]) && !estePixelAlb(bitmapImage[j][i+3])
		&& estePixelAlb(bitmapImage[j+1][i+1]) && !estePixelAlb(bitmapImage[j+4][i]))
		return 0;
	if (estePixelAlb(bitmapImage[j+1][i]) && !estePixelAlb(bitmapImage[j+1][i+4]) &&  !estePixelAlb(bitmapImage[j+3][i])
		&& estePixelAlb(bitmapImage[j+3][i+4]) && !estePixelAlb(bitmapImage[j+2][i+2]) && !estePixelAlb(bitmapImage[j+4][i+2])
		&& !estePixelAlb(bitmapImage[j][i+2]) && !estePixelAlb(bitmapImage[j][i+3]) && estePixelAlb(bitmapImage[j+1][i+1])
		&& !estePixelAlb(bitmapImage[j+4][i]))
		return 2;
	if (estePixelAlb(bitmapImage[j+1][i]) && !estePixelAlb(bitmapImage[j+1][i+4]) &&  estePixelAlb(bitmapImage[j+3][i])
		&& !estePixelAlb(bitmapImage[j+3][i+4]) && !estePixelAlb(bitmapImage[j+2][i+2]) && !estePixelAlb(bitmapImage[j+4][i+2])
		&& !estePixelAlb(bitmapImage[j][i+2]) && !estePixelAlb(bitmapImage[j][i+3]) && !estePixelAlb(bitmapImage[j+4][i]))
		return 3;
	if (!estePixelAlb(bitmapImage[j+1][i]) && !estePixelAlb(bitmapImage[j+1][i+4]) &&  estePixelAlb(bitmapImage[j+3][i])
		&& !estePixelAlb(bitmapImage[j+3][i+4]) && !estePixelAlb(bitmapImage[j+2][i+2]) && estePixelAlb(bitmapImage[j+4][i])
		&& estePixelAlb(bitmapImage[j+4][i+2]) && estePixelAlb(bitmapImage[j][i+2]) && estePixelAlb(bitmapImage[j+1][i+1])
		&& estePixelAlb(bitmapImage[j+3][i+2]) && estePixelAlb(bitmapImage[j+3][i+1]))
		return 4;
	if (!estePixelAlb(bitmapImage[j+1][i]) && estePixelAlb(bitmapImage[j+1][i+4]) &&  estePixelAlb(bitmapImage[j+3][i])
		&& !estePixelAlb(bitmapImage[j+3][i+4]) && !estePixelAlb(bitmapImage[j+2][i+2]) && !estePixelAlb(bitmapImage[j+4][i+2])
		&& !estePixelAlb(bitmapImage[j][i+2]) && !estePixelAlb(bitmapImage[j][i+3]) && estePixelAlb(bitmapImage[j+1][i+1])
		&& !estePixelAlb(bitmapImage[j+4][i]))
		return 5;
	if (!estePixelAlb(bitmapImage[j+1][i]) && estePixelAlb(bitmapImage[j+1][i+4]) &&  !estePixelAlb(bitmapImage[j+3][i])
		&& !estePixelAlb(bitmapImage[j+3][i+4]) && !estePixelAlb(bitmapImage[j+2][i+2]) && !estePixelAlb(bitmapImage[j][i+2])
		&& !estePixelAlb(bitmapImage[j+4][i+2]) && !estePixelAlb(bitmapImage[j][i+2]) && !estePixelAlb(bitmapImage[j][i+3])
		&& estePixelAlb(bitmapImage[j+1][i+1]) && !estePixelAlb(bitmapImage[j+4][i]))
		return 6;
	if (estePixelAlb(bitmapImage[j+1][i]) && !estePixelAlb(bitmapImage[j+1][i+4]) &&  estePixelAlb(bitmapImage[j+3][i])
		&& !estePixelAlb(bitmapImage[j+3][i+4]) && estePixelAlb(bitmapImage[j+2][i+2]) && estePixelAlb(bitmapImage[j+4][i])
		&& estePixelAlb(bitmapImage[j+4][i+2]) && !estePixelAlb(bitmapImage[j][i+2]) && !estePixelAlb(bitmapImage[j][i+3])
		&& estePixelAlb(bitmapImage[j+1][i+1]) && estePixelAlb(bitmapImage[j+4][i]))
		return 7;
	if (!estePixelAlb(bitmapImage[j+1][i]) && !estePixelAlb(bitmapImage[j+1][i+4]) &&  !estePixelAlb(bitmapImage[j+3][i])
		&& !estePixelAlb(bitmapImage[j+3][i+4]) && !estePixelAlb(bitmapImage[j+2][i+2]) && !estePixelAlb(bitmapImage[j+4][i+2])
		&& !estePixelAlb(bitmapImage[j][i+2]) && !estePixelAlb(bitmapImage[j][i+3]) && estePixelAlb(bitmapImage[j+1][i+1])
		&& !estePixelAlb(bitmapImage[j+4][i]))
		return 8;
	if (!estePixelAlb(bitmapImage[j+1][i]) && !estePixelAlb(bitmapImage[j+1][i+4]) &&  estePixelAlb(bitmapImage[j+3][i])
		&& !estePixelAlb(bitmapImage[j+3][i+4]) && !estePixelAlb(bitmapImage[j+2][i+2]) && !estePixelAlb(bitmapImage[j+4][i+2])
		&& !estePixelAlb(bitmapImage[j][i+2]) && !estePixelAlb(bitmapImage[j][i+3]) && estePixelAlb(bitmapImage[j+1][i+1])
		&& !estePixelAlb(bitmapImage[j+4][i]))
		return 9;
	return -1;
}

//Functia determinaCifre imi scre in fiserul de iesire cifrele care se afla in imagine , functie corespondenta task-ului 2 
void determinaCifre(FILE *outputFile, pixel **bitmapImage, int width, int height)
{
	int i, j, cifra = -1;
	for (i = 0; i < width - 4; i++)
	{
		for (j = 0; j < height - 4; j++)
		{
			if (!estePixelAlb(bitmapImage[j][i]))
			{
				//determina cifra care are in coltul din stanga sus pixelul bimapImage[j][i] altfel returneaza -1
				cifra = determinaCifra(bitmapImage, i, j);
				if (cifra != -1)
				{
					fprintf(outputFile, "%d", cifra);
					break;
				}
			}
			else
			{
				//determina cifra 1
				cifra = determinaCifra1(bitmapImage, i, j, width);
				if (cifra == 1)
				{
					fprintf(outputFile, "%d", cifra);
					break;
				}
			}
		}
	}
}

int main()
{
	bmp_infoheader bitmapInfoHeader;
	bmp_fileheader bitmapFileHeader;
	pixel **bitmapData;
	int padding, counter = 0, i, j, padVal, k;
	unsigned char *pixelArray;
	char *buffer, *outputFileName, *outputFileName2, *outputFileName3;
	int Blue = 0, Green = 0 ,Red = 0, *numere, numarCifre = 0;
	int coloane[100], linii[100];

	FILE *outputBitmapFile;
	FILE *input;
	FILE *outputTextFile;
	FILE *outputbitmapFile2;

	input = fopen("input.txt","rt");
	if (input == NULL)
		return 0;

	buffer = (char*)malloc(BUFF_SIZE * sizeof(char));

	fgets(buffer, BUFF_SIZE, input);
	buffer = (char*)realloc(buffer,(strlen(buffer) + 1) * sizeof(char));
	strtok(buffer, "\n");

	outputFileName = (char*)malloc(BUFF_SIZE * sizeof(char));
	//redenumirea numelui al fisierului de iesire
	for ( i = 0; i < strlen(buffer); i++)
	{
		if (buffer[i] == '.')
			break;
		outputFileName[i] = buffer[i];
	}
	outputFileName[i]='\0';

	strcat(outputFileName, "_task1.bmp");
	outputFileName = (char*)realloc(outputFileName,(strlen(outputFileName) + 1) * sizeof(char));
	outputBitmapFile = fopen(outputFileName,"wb");

	//citirea valorile de la task-ul 2 din fisier
	fscanf(input, "%d", &Blue);
	fscanf(input, "%d", &Green);
	fscanf(input, "%d", &Red);

	bitmapData = LoadBitmapFile(buffer, &bitmapInfoHeader, &bitmapFileHeader);

	fwrite(&bitmapFileHeader, sizeof(bmp_fileheader), 1, outputBitmapFile);
	fwrite(&bitmapInfoHeader, sizeof(bmp_infoheader), 1, outputBitmapFile);
	padding = (4 - (3 * bitmapInfoHeader.width) % 4) % 4;

	pixelArray = (unsigned char *)malloc((3 * bitmapInfoHeader.width + padding) * bitmapInfoHeader.height);

	//Task1 , inlocuire culoare 
	for(i = bitmapInfoHeader.height - 1; i >= 0; i--) {
		for( j = 0; j < bitmapInfoHeader.width; j++) {

			pixelArray[counter++] = bitmapData[i][j].B;
			pixelArray[counter++] = bitmapData[i][j].G;
			pixelArray[counter++] = bitmapData[i][j].R;

			if(!(bitmapData[i][j].B == 255 && bitmapData[i][j].G == 255 && bitmapData[i][j].R == 255))
			{
				pixelArray[counter-3] = (unsigned char)Blue;
				pixelArray[counter-2] = (unsigned char)Green;
				pixelArray[counter-1] = (unsigned char)Red;
			}
		}
		for (padVal = 0; padVal < padding; padVal++) 
			pixelArray[counter++] = 0;
	}
	fwrite((unsigned char*) pixelArray, (3 * bitmapInfoHeader.width + padding) * bitmapInfoHeader.height, 1, outputBitmapFile);

	//task2

	outputFileName2 = (char*)malloc(BUFF_SIZE * sizeof(char));

	for ( i = 0; i < strlen(buffer); i++)
	{
		if (buffer[i] == '.')
			break;
		outputFileName2[i] = buffer[i];
	}
	outputFileName2[i]='\0';

	strcat(outputFileName2, "_task2.txt");
	outputFileName2 = (char*)realloc(outputFileName2,(strlen(outputFileName2) + 1) * sizeof(char));
	outputTextFile = fopen(outputFileName2,"wt");
	determinaCifre(outputTextFile, bitmapData, bitmapInfoHeader.width, bitmapInfoHeader.height);

	//task3
	counter=0;
	outputFileName3 = (char*)malloc(BUFF_SIZE * sizeof(char));

	for ( i = 0; i < strlen(buffer); i++)
	{
		if (buffer[i] == '.')
			break;
		outputFileName3[i] = buffer[i];
	}
	outputFileName3[i]='\0';
	strcat(outputFileName3, "_task3.bmp");
	outputFileName3 = (char*)realloc(outputFileName3,(strlen(outputFileName3) + 1) * sizeof(char));
	outputbitmapFile2 = fopen(outputFileName3,"wb");

	//creare imagine
	fwrite(&bitmapFileHeader, sizeof(bmp_fileheader), 1, outputbitmapFile2);
	fwrite(&bitmapInfoHeader, sizeof(bmp_infoheader), 1, outputbitmapFile2);
	counter = 0 ;
	numere = (int*)malloc(BUFF_SIZE * sizeof(int));

	while (fscanf(input,"%d",&numere[counter]))
	{	
		counter++;

	}
	eliminaCifre(bitmapData, bitmapInfoHeader.width, bitmapInfoHeader.height, linii, coloane, &numarCifre, numere, counter);

	k = 0;
	for (i = bitmapInfoHeader.height - 1; i >= 0; i--) 
	{
		for ( j = 0; j < bitmapInfoHeader.width; j++) 
		{

			pixelArray[k++] = bitmapData[i][j].B;
			pixelArray[k++] = bitmapData[i][j].G;
			pixelArray[k++] = bitmapData[i][j].R;
		}
		for (padVal = 0; padVal < padding; padVal++) 
			pixelArray[k++] = 0;
	}
	
	fwrite((unsigned char*) pixelArray, (3 * bitmapInfoHeader.width + padding) * bitmapInfoHeader.height, 1, outputbitmapFile2);
	
	fcloseall();
	for(i = 0; i < bitmapInfoHeader.height; i++)
		free(bitmapData[i]);
	free(bitmapData);
	free(buffer);
	free(outputFileName);
	free(pixelArray);
	free(outputFileName3);
	free(numere);
	return 0;
}
