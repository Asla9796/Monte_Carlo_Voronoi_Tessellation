#include "voronoi_mc.h"

int main(int argc, char** argv )
{
    if ( argc != 2 )
    {
        printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    }
    
    int i, j, nrand, t;
    int x, y, neighbour;
    double check;
    J=100;
    kb=1.38;
    T=1000;
    maxrun=10000;
    N=500;
    
    Mat image, image0;
    image0 = imread( argv[1], 1 );
    nx = image0.rows;
    ny = image0.cols;
    nz = 3;
    
    if ( !image0.data )
    {
        printf("No image data \n");
        return -1;
    }
    
    printf("\nnx=%d, ny=%d", nx, ny);
    
    //rgb2greyscale(image0, nx, ny);
    image = image0.clone();
       
    srand(time(NULL));
    for(t=0; t<maxrun; t++)
    {
        printf("\nTimestep: %d", t);
        
        h0=0.0;
        h=0.0;
        image=image0.clone();
        for(nrand=0; nrand<N; nrand++)
        {
            x=(int)((double)rand()/RAND_MAX*(nx-3)+1.0);
            y=(int)((double)rand()/RAND_MAX*(ny-3)+1.0);

            if(image0.at<Vec3b>(x,y).val[0]!=image0.at<Vec3b>(x-1,y).val[0])
                h0+=J*0.5;
            if(image0.at<Vec3b>(x,y).val[0]!=image0.at<Vec3b>(x+1,y).val[0])
                h0+=J*0.5;
            if(image0.at<Vec3b>(x,y).val[0]!=image0.at<Vec3b>(x,y-1).val[0])
                h0+=J*0.5;
            if(image0.at<Vec3b>(x,y).val[0]!=image0.at<Vec3b>(x,y+1).val[0])
                h0+=J*0.5;
            if(image0.at<Vec3b>(x,y).val[0]!=image0.at<Vec3b>(x-1,y+1).val[0])
                h0+=J*0.5;
            if(image0.at<Vec3b>(x,y).val[0]!=image0.at<Vec3b>(x-1,y-1).val[0])
                h0+=J*0.5;
            if(image0.at<Vec3b>(x,y).val[0]!=image0.at<Vec3b>(x+1,y+1).val[0])
                h0+=J*0.5;
            if(image0.at<Vec3b>(x,y).val[0]!=image0.at<Vec3b>(x+1,y-1).val[0])
                h0+=J*0.5;
                
            neighbour=(int)((double)rand()/RAND_MAX*7);
            image.at<Vec3b>(x,y).val[0]=image0.at<Vec3b>(x+order[neighbour][0],y+order[neighbour][1]).val[0];
            image.at<Vec3b>(x,y).val[1]=image0.at<Vec3b>(x+order[neighbour][0],y+order[neighbour][1]).val[1];
            image.at<Vec3b>(x,y).val[2]=image0.at<Vec3b>(x+order[neighbour][0],y+order[neighbour][1]).val[2];
            
            if(image.at<Vec3b>(x,y).val[0]!=image.at<Vec3b>(x-1,y).val[0])
                h+=J*0.5;
            if(image.at<Vec3b>(x,y).val[0]!=image.at<Vec3b>(x+1,y).val[0])
                h+=J*0.5;
            if(image.at<Vec3b>(x,y).val[0]!=image.at<Vec3b>(x,y-1).val[0])
                h+=J*0.5;
            if(image.at<Vec3b>(x,y).val[0]!=image.at<Vec3b>(x,y+1).val[0])
                h+=J*0.5;
            if(image.at<Vec3b>(x,y).val[0]!=image.at<Vec3b>(x-1,y+1).val[0])
                h+=J*0.5;
            if(image.at<Vec3b>(x,y).val[0]!=image.at<Vec3b>(x-1,y-1).val[0])
                h+=J*0.5;
            if(image.at<Vec3b>(x,y).val[0]!=image.at<Vec3b>(x+1,y+1).val[0])
                h+=J*0.5;
            if(image.at<Vec3b>(x,y).val[0]!=image.at<Vec3b>(x+1,y-1).val[0])
                h+=J*0.5;
            
        }

        p=exp(-(h-h0)/(kb*T));
        check = (double)rand()/RAND_MAX;
        printf("\nprobability = %lf, randnumber = %lf", p, check);
        printf("\nh %lf h0 %lf", h, h0);
        
        if(check<=p)
        {
            printf("\nEvolving");
            count += 1;
            image0=image.clone();
        }
        
    }

    display(image);
    printoutput(image, nx, ny);
    printf("\nNumber of updates = %d", count);
    std::cout<<"\nProgram end. Exiting\n";
    return 0;
}

Mat rgb2greyscale(Mat image, int nx, int ny)
{
    int i, j;
    double wr, wg, wb;
    wr = 0.3; wg = 0.59; wb = 0.11;
    for(i=0; i<nx; i++)
    {
        for(j=0; j<ny; j++)
        {
            image.at<Vec3b>(i,j).val[0] = (int)(wr*image.at<Vec3b>(i,j).val[0]+wg*image.at<Vec3b>(i,j).val[1]+wb*image.at<Vec3b>(i,j).val[2]);
            image.at<Vec3b>(i,j).val[1] = image.at<Vec3b>(i,j).val[0];
            image.at<Vec3b>(i,j).val[2] = image.at<Vec3b>(i,j).val[0];
        }
    }
    return image;
}

void display(Mat image)
{
    namedWindow("Display Image", WINDOW_NORMAL);
    imshow("Display Image", image);
    waitKey(0);
    return;
}

void printoutput(Mat image, int nx, int ny)
{
    int i,j;
    FILE *fp;
    char filename[100];
  
    sprintf (filename, "image.dat");
    printf("\n Starting output of temperature to %s ...\n",filename);

    fp=fopen(filename,"w");
  
    fprintf(fp, "image = [");
    for (i=0; i<nx; i++)
    {
        for(j=0; j<ny; j++)
        {
            fprintf(fp, "%d  ", image.at<Vec3b>(i,j).val[0]);
        }
        fprintf(fp,"\n");
    }
    fprintf(fp, "];\n");
    fclose(fp);
  
    printf("\n...............done.................\n");
    return;
}