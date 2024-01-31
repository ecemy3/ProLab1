#include<graphics.h>
#include <stdio.h>
#include <string.h>
void DrillCostCalc(int *platform,int *Drill);
void CalcArea(int coordinatesX[],int coordinatesY[],int lenght);
void DisplayDrillArea(int arrayX[],int arrayY[],int topX,int topY,int lowestX,int lowestY,int lenght,int platform,int drill,int rezerv);
int GetSizeOfArray(char *array)
{
	int count=0;
	for(int i =0; array[i]!=NULL; i++)
	{
		count++;
	}
	return count;
}
int GetSizeOfArrayInt(int array[])
{
	int count=0;
	for(int i =0; array[i]!=NULL; i++)
	{
		count++;
	}
	return count;
}
int CheckForInt(char *array,int lenght)
{
	int i=0;
	while((int)array[lenght+i] >= 48 && (int)array[lenght+i] <=57)
	{
		i++;
	}
	return i;
}
void DisplayBackground()
{
	for(int i=0;i<1600;i+=8)
	{
		setcolor(7);
		line(0,i,2000,i);
		line(i,0,i,2000); 
	}
}
	void DisplayShape(int lenght,int coordinateX[],int coordinateY[])
{
	int newArrayX[lenght];
	int newArrayY[lenght];
	int newArrayX2[lenght];
	int newArrayY2[lenght];
	int newArrayX3[lenght];
	int newArrayY3[lenght];
	int count3=0;
	int count2=0;

	for(int i=0;i<lenght;i++)
	{
		if((coordinateX[i] == coordinateX[0] && coordinateY[i] == coordinateY[0]) && (i!=0) && i!=lenght-1)
		{     //  10    14  4(5)        
			int z = lenght-i;   // Toplam uzunluktan ilk elde edilen þeklin uzunluðu çýkartýlarak sonraki þekle kalan uzunluk bulunur.
			for(int k=0;k<z;k++)
			{
				if((coordinateX[k+i+1] == coordinateX[i+1] && coordinateY[k+i+1] == coordinateY[i+1]) && k != 0 ) 
				{
					count2 = k+1;
				}
			}
			count3 = z - count2 -1;
			for(int l=0;l<lenght-count3-count2;l++)
		    {
		    	newArrayX[l] = coordinateX[l];
		    	newArrayY[l] = coordinateY[l];
		    }
		    CalcArea(newArrayX,newArrayY,lenght-count2-count3);
			
			for(int g=0;g<count2 ;g++)     // 2nd shape
			{
				newArrayX2[g] = coordinateX[g+i+1];
				newArrayY2[g] = coordinateY[g+i+1];
			}
			 CalcArea(newArrayX2,newArrayY2,count2);

            if(count3 > 1)
            {
            	for(int g=0;g<count3 ;g++)     // 3nd shape
				{
					newArrayX3[g] = coordinateX[g+i+1+count2];
					newArrayY3[g] = coordinateY[g+i+1+count2];
				}
			    CalcArea(newArrayX3,newArrayY3,count3);
			}
		    return;
		}
	}
	CalcArea(coordinateX,coordinateY,lenght);
}
void SeperateArray(char *array, int coordinateX[],int coordinateY[],int lenght,int *countOfCoordinates)
{
	int tempInt;
	char theArray[lenght];
	int lenght2=0;
    int k=0;
    strcpy(theArray,array);
    
	for(int i=0;i<lenght;i++)
	{
		char numberX[20]={};
        char numberY[20]={};
		if(array[i] =='(')
		{		
		   int x = CheckForInt(theArray,i+1);   // for X axis
		   for(int k=0;k<x;k++)
		   {
		   	    numberX[k] = theArray[i+1+k];
		   }
		   lenght2 += x-1;
		   
           sscanf(numberX,"%d",&tempInt);
		   coordinateX[k] = tempInt;
		   
		   int y = CheckForInt(theArray,i+3+lenght2);   // for Y axis
		   for(int k=0;k<y;k++)
		   {
		   	    numberY[k] = theArray[i+3+k+lenght2];
		   }

           sscanf(numberY,"%d",&tempInt);
		   coordinateY[k] = tempInt;
		   lenght2=0;
		   k++;
		}
	}
	*countOfCoordinates=k; // vertices count
}
void CalcArea(int coordinatesX[],int coordinatesY[],int lenght)
{
	int totalPoints =0;
	int topX=0;
	int lowestX = INT_MAX;
	int topY=0;
	int lowestY = INT_MAX;
	
	for(int i=0;i<lenght;i++)
	{
		if(topX <= coordinatesX[i])
		{
			topX = coordinatesX[i];
		}
		if(lowestX >= coordinatesX[i])
		{
			lowestX = coordinatesX[i];
		}
		if(topY <= coordinatesY[i])
		{
			topY = coordinatesY[i];
		}
		if(lowestY >= coordinatesY[i])
		{
			lowestY = coordinatesY[i];
		}
	}
	float area=0;
	float isNegativeX=0;
	float isNegativeY=0;
	float isNegative;
	float totalArea;
	for(int i=0;i<lenght-1;i++)
	{
		isNegativeX = (float)(coordinatesX[i]-coordinatesX[i+1]);
		isNegativeY = (float)(coordinatesY[i]-coordinatesY[i+1]);
		isNegative = isNegativeY * isNegativeX;
		
		if(isNegative > 0)
		area += isNegative/2.0f;
		else if(isNegative < 0)
		area += -isNegative/2.0f;
		
		if(isNegativeX < 0)
			isNegativeX = -isNegativeX;
		if(isNegativeY < 0)
			isNegativeY = -isNegativeY;
			
		float tan=1;
		if(isNegativeX != 0 && isNegativeY !=0)
		tan = isNegativeY / isNegativeX;
		
		if(isNegativeY != 0) // ADDING EXTRA DOTS
		{
			if (tan == 1 || tan == (int)tan )  // tanjantýn herhangi bir katsayi olup olmadigi kontrol edilir bunun sebebi eðer zaten tam katsayýya denk geliyorsa hata payý 0 a inecektir,
			{ 
			                           // bu sebeple 1 eklememize gerek kalmaz...
				area -= (isNegativeX/2)*tan;
			}
			else if(tan < 1)
			{
				tan = 1;
				area -= (isNegativeX/2)*tan+tan; // 1*tan (tan < 1) 'ý 1 e yuvarladýk.
			}
			else if(tan > 1)
			{
				tan = 2;
				area -= (isNegativeX/2)*tan+tan;  // 1*tan (tan > 1 )'ý 2 ye yuvarladýk.
			}	
		}
	}	
	for(int i=0;i<100;i+=1)
	{
		for(int k=0;k<100;k+=1)
		{
			if((lowestX <= i && i < topX) && (lowestY <= k && k < topY))
			{
			   totalPoints++;	// All points in square,
			}
		}
	}
	totalArea = totalPoints-area;
	printf("\n Alan : %.2f ",totalArea);
	printf("\n Rezerv degeri : %.0f \n",totalArea*10);

	totalPoints=0;
	
	int xArray[400];
	int yArray[400];
	int index=0;
	int multipliedWithNegativeX=0;
	int multipliedWithNegativeY=0;

	for(int k=0;k<lenght-1;k++)
	{
		float tempX = (float)coordinatesX[k]-coordinatesX[k+1];
		float tempY = (float)coordinatesY[k]-coordinatesY[k+1];
		float temp;
		
		if(tempX < 0)
		{
			tempX = -tempX;
			multipliedWithNegativeX = 1;
		}
		if(tempY < 0)
		{
			tempY= -tempY;
			multipliedWithNegativeY = 1;
		}
		
		temp = tempY/tempX; 
		float holdTemp = temp;
		temp = (int)temp;		
		
		for(int i=0;i<=tempX;i++)     // KARE DIÞINDAKÝ DAHÝL NOKTALAR
		{
			if(temp != (int)temp)                         // 
			{
			if(multipliedWithNegativeX == 0)
				xArray[index] = coordinatesX[k+1]+i*temp;
			else
				xArray[index] = coordinatesX[k+1]-i*temp;
			if(multipliedWithNegativeY == 0)
				yArray[index] = coordinatesY[k+1]+temp*i;  // çarpma sebebi -> artýþ miktarý
            else
            	yArray[index] = coordinatesY[k+1]-temp*i;
			}
			else
			{
		    tempY = holdTemp;
		
			if(multipliedWithNegativeX == 0)
				xArray[index] = coordinatesX[k+1]+i;
			else
				xArray[index] = coordinatesX[k+1]-i;
			if(multipliedWithNegativeY == 0)
				yArray[index] = coordinatesY[k+1]+tempY*i;  // çarpma sebebi -> artýþ miktarý
            else
            	yArray[index] = coordinatesY[k+1]-tempY*i;
			}
			
			index++;
		}
		multipliedWithNegativeX = 0;
		multipliedWithNegativeY = 0;
	}
	
	int topX2,topY2,lowY=INT_MAX,lowX=INT_MAX;
	
	for(int i=0;i<index;i++)
	{
		if(topX <= xArray[i])
		{
			topX2 = xArray[i];
		}
		if(lowestX >= xArray[i])
		{
			lowX = xArray[i];
		}
		if(topY <= yArray[i])
		{
			topY2 = yArray[i];
		}
		if(lowestY >= yArray[i])
		{
			lowY = yArray[i];
		}
	}
	
	int arr[lenght*2];
	int sumIndex=0;
	for(int i=0;i<lenght;i++)
	{
		arr[sumIndex] = coordinatesX[i]*8;
		arr[sumIndex+1] = coordinatesY[i]*8-20; // painting inside the shape...
		sumIndex+=2;
	}
	setcolor(1);
	setfillstyle(SOLID_FILL,9);
	fillpoly(lenght,arr);
    int platform;
    int drill;
    DrillCostCalc(&platform,&drill);
	DisplayDrillArea(xArray,yArray,topX2,topY2,lowX,lowY,index,platform,drill,totalArea*10);
	
}
void DisplayDrillArea(int arrayX[],int arrayY[],int topX,int topY,int lowestX,int lowestY,int lenght,int platform,int drill,int rezerv)
{
	int count=0;
	setcolor(7);
	
	for(int i=0;i<lenght;i+=1)     // FOR IN-SQUARE 
     	{
     		for(int k=0;k<lenght;k+=1)
     		{
     			if(((arrayX[i] == arrayX[k]) || (arrayY[i] == arrayY[k])) && i!=k)
     			{
     				count+=2;
				}
			}	    	
     	}
     	int displayX[count];
		int displayY[count];
		int index=0;
    for(int i=0;i<lenght;i+=1)
     	{
     		for(int k=0;k<lenght;k+=1)
     		{
     			if(((arrayX[i] == arrayX[k]) || (arrayY[i] == arrayY[k])) && i!=k)
     			{
     				displayX[index]   = arrayX[i];
     				displayX[index+1] = arrayX[k];
     				displayY[index]   = arrayY[i];
     				displayY[index+1] = arrayY[k];
     				index+=2;
				}
			}	   
     	}
     	int color =0;
     	int drillCostTotal=0;
     	int val=0;
     	int platformCostTotal=0;
		for(int i=0;i<count;i+=platform)
    {
    	if(displayY[i] == displayY[i+1] || displayX[i] == displayX[i+1])
    	{
			setcolor(11);    	
    		setlinestyle(0,2,2);
    		
    		if(displayY[i] - displayY[i+1] != 0)
    		val = displayY[i]-displayY[i+1];
    		if(displayX[i] - displayX[i+1] != 0)
    		val = displayX[i]-displayX[i+1];
    		
      		if(val < 0)
    		val = -val;	
    		
    		drillCostTotal += val*drill;
    		platformCostTotal += platform;
    		line(8*displayX[i],8*displayY[i]-20,8*displayX[i+1],8*displayY[i+1]-20);
    	}
	}
	printf("\n Toplam Kar:");
	printf("\n %d - %d - %d = %d",rezerv,drillCostTotal,platformCostTotal,rezerv-drillCostTotal-platformCostTotal);
    
}
void DrillCostCalc(int *platform,int *Drill)
{	
	int DrillCost;
	int PlatformCost;
	
	printf("Lutfen Sondaj Maaliyeti Belirleyiniz.\n");
	do
	{
		scanf("%d",&DrillCost);	
	}while(DrillCost < 0 || DrillCost > 10);
	printf("Lutfen Platform Maaliyeti Belirleyiniz.\n");
	scanf("%d",&PlatformCost);
	*platform = PlatformCost;
	*Drill = DrillCost;
	
}
int main( ){
	    int satir;
	    do
		{
		   printf("Lutfen cizdirilmesini istediginiz satiri giriniz:");
		   scanf("\n %d",&satir);
		}
		while(satir<0 || satir > 2);
		
        initwindow( 1920 , 1080 , "Rezerv Kar Hesaplayýcý");
        floodfill(1,1,WHITE);
 	    system("curl http://bilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt > deneme.txt");
        int i=0;
        FILE *file;
        char allLines[600];
        char *_line1;
		char line1[400];
		char line2[400];
		int firstCoordinatesX[400];
		int firstCoordinatesY[400];
		int secondCoordinatesX[400];
		int secondCoordinatesY[400];
		int countOfCoordinates1;
		int countOfCoordinates2;
		
		file = fopen("deneme.txt","r");
		
		fgets(line1,100,file);  // ilk 50 yi okuduktan sonra aþaðýda 2. satýr ona kalýyor.
		
		if(file != NULL)
		{			
			while (fgets(line2, 100, file) != NULL)
	        {
			    break;
	    	}
	    }
	    else
	    {
	    	printf("An error occured.");
		}
        DisplayBackground();
        if(satir == 1)
        {
        	SeperateArray(line1,firstCoordinatesX,firstCoordinatesY,GetSizeOfArray(line1),&countOfCoordinates1);
            DisplayShape(countOfCoordinates1,firstCoordinatesX,firstCoordinatesY);
		}
		else if(satir == 2)
		{
			SeperateArray(line2,secondCoordinatesX,secondCoordinatesY,GetSizeOfArray(line2),&countOfCoordinates2);
			DisplayShape(countOfCoordinates2,secondCoordinatesX,secondCoordinatesY);
		}
        fclose(file);
        getch();
        return 0;
}
