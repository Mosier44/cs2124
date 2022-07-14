#include "graph.h"
#include "graphPathAlg.h"



/* printNames
 * input: none
 * output: none
 *
 * Prints names of the students who worked on this solution
 */
void printNames( )
{
    /* TODO : Fill in you and your partner's names (or N/A if you worked individually) */
    printf("This solution was completed by:\n");
    printf("<student name #1> Colton Mosier\n");
    printf("<student name #2> N/A\n");
}

/* OPTIONAL HELPER FUNCTION
 * buildGraph
 *
 * IMPORTANT NOTE: This is an entirely optional helper function which is only called by student implemented functions.
 * Creates a new graph to represent the given maze.  
 */
Graph* buildGraph( array2D* maze )
{
    //OPTIONAL TODO: Translate the given maze into a graph.  'X' represents impassable locations.  Only moves of up, down, left, and right are allowed. 
    /* With the right parameters this can be used by all three functions below to build the graph representing their different maze problems. */
    /* HINT 1: To solve this, my solution used the functions createGraph and setEdge from graph.c */
    /* HINT 2: My solution also used createPoint from point2D.c */

    return NULL; /* TODO: Replace with your graph representing maze */
}

/* hasPath
 * input: an array2D pointer to a maze
 * output: pathResult
 *
 * Detects whether a path exists from 'S' to 'F' in the graph. 'X' marks impassable regions.
 */
pathResult hasPath( array2D *maze )
{
    int distance, x, y, capacity = 0;
    Point2D startingPoint;
    Point2D endPoint;
    Point2D currentPoint;
    Point2D nextPoint = createPoint( 0, 0 );

    // Counts the amount of spaces in the matrix that doesn't have 'X' also assigns startingPoint and endPoint
    for ( x = 0; x < maze->length; x++)
    {
        for ( y = 0; y < maze->width; y++)
        {
            if ( maze->array2D[x][y] != 'X' )
            {
                capacity++;
            }
            if ( maze->array2D[x][y] == 'S' )
            {
                startingPoint = createPoint( x, y );
            }
            if ( maze->array2D[x][y] == 'F')
            {
                endPoint = createPoint( x, y );
            }       
        } 
    }

    Graph* myGraph = createGraph( capacity );

    // Loops through matrix finding all vertex's edges until endPoint is found.
    for(x = 0; x < maze->length; x++ )
    {
        for( y = 0; y < maze->width; y++)
        {
            if(maze->array2D[x][y] != 'X')
            {
                currentPoint.x = x;
                currentPoint.y = y;
                if ( maze->array2D[x+1][y] != 'X')
                {
                    nextPoint.x = x+1;
                    nextPoint.y = y;
                    setEdge( myGraph, currentPoint, nextPoint, 1);
                }
                if ( maze->array2D[x-1][y] != 'X')
                {
                    nextPoint.x = x-1;
                    nextPoint.y = y;
                    setEdge( myGraph, currentPoint, nextPoint, 1);
                }
                if ( maze->array2D[x][y+1] != 'X')
                {
                    nextPoint.x = x;
                    nextPoint.y = y+1;
                    setEdge( myGraph, currentPoint, nextPoint, 1);
                }
                if ( maze->array2D[x][y-1] != 'X')
                {
                    nextPoint.x = x;
                    nextPoint.y = y-1;
                    setEdge( myGraph, currentPoint, nextPoint, 1);
                }
            }
        }
    }

    // update dijkstras 
    dijkstrasAlg( myGraph, startingPoint );

    // get results from dijkstras to see if path is found
    distance = getDistance( myGraph, startingPoint, endPoint );

    freeGraph(myGraph);

    if ( distance > 0 && distance < INT_MAX )
    {
        return PATH_FOUND;
    }
    else
        return PATH_IMPOSSIBLE; /* TODO: Replace with PATH_FOUND or PATH_IMPOSSIBLE based on whether a path exists */
    
}

/* findNearestFinish
 * input: an array2D pointer to a maze, a pointer to an int
 * output: pathResult
 *
 * The maze contains one 'S' and multiple 'F's (1 or more).  'X' marks impassable regions.
 * Find the length of the shortest path to any 'F' from 'S' and return it in spDist.
 * If no 'F' is reachable set spDist to INT_MAX.
 */
pathResult findNearestFinish( array2D *maze, int *spDist )
{
    int x = 0, y = 0, j = 0, i = 0, capacity = 0, min = 0;
    Point2D startingPoint;
    Point2D currentPoint;
    Point2D nextPoint = createPoint( 0, 0 );

    typedef struct finalPoints{
        int distance;
        int x;
        int y;
        Point2D ending;
    }finalPoints;

    finalPoints points[12];

    for ( x = 0; x < maze->length; x++)
    {
        for ( y = 0; y < maze->width; y++)
        {
            if ( maze->array2D[x][y] != 'X' )
            {
                capacity++;
            }
            if ( maze->array2D[x][y] == 'S' )
            {
                startingPoint = createPoint( x, y );
            }
            if ( maze->array2D[x][y] == 'F')
            {
                points[j].x = x;
                points[j].y = y;
                j++;
            }       
        } 
    }

    Graph* myGraph = createGraph( capacity );

    // Loops through matrix finding all vertex's edges 
    for(x = 0; x < maze->length; x++ )
    {
        for( y = 0; y < maze->width; y++)
        {
            if(maze->array2D[x][y] != 'X')
            {
                currentPoint.x = x;
                currentPoint.y = y;
                if ( maze->array2D[x+1][y] != 'X')
                {
                    nextPoint.x = x+1;
                    nextPoint.y = y;
                    setEdge( myGraph, currentPoint, nextPoint, 1);
                }
                if ( maze->array2D[x-1][y] != 'X')
                {
                    nextPoint.x = x-1;
                    nextPoint.y = y;
                    setEdge( myGraph, currentPoint, nextPoint, 1);
                }
                if ( maze->array2D[x][y+1] != 'X')
                {
                    nextPoint.x = x;
                    nextPoint.y = y+1;
                    setEdge( myGraph, currentPoint, nextPoint, 1);
                }
                if ( maze->array2D[x][y-1] != 'X')
                {
                    nextPoint.x = x;
                    nextPoint.y = y-1;
                    setEdge( myGraph, currentPoint, nextPoint, 1);
                }
            }
        }
    }

    dijkstrasAlg( myGraph, startingPoint );

    for( i = 0; i < j; i++ )
    {
        points[i].ending = createPoint( points[i].x,points[i].y );
    }

    for ( i = 0; i < j; i++)
    {
        points[i].distance = getDistance( myGraph, startingPoint, points[i].ending);
    }

    min = points[0].distance;
    for ( i = 0; i < j; i++)
    {
        if ( points[i].distance < min)
        {
            min = points[i].distance;
        }
    }
    
    freeGraph(myGraph);

    if ( min != INT_MAX )
    {
        (*spDist) = min;
        return PATH_FOUND;
    }

    (*spDist) = INT_MAX;
    return PATH_IMPOSSIBLE;
}

/* findTunnelRoute
 * input: an array2D pointer to a maze, an int representing the number X's you can travel through
 * output: pathResult
 *
 * Detects whether a path exists from 'S' to 'F' in the graph where you pass through at most k 'X' symbols.
 */
pathResult findTunnelRoute( array2D *maze, int exploisives )
{
    //TODO: Complete this function
    /* HINT 1: To solve this, my solution used the functions createGraph, freeGraph, setEdge, dijkstrasAlg, getDistance from graph.c */
    /* HINT 2: My solution also used createPoint from point2D.c */
    /* HINT 3: You might also consider using the new helper function buildGraph to build the graph representing maze. */
    int distance = 0, x = 0, y = 0, capacity = 0;
    Point2D startingPoint;
    Point2D endPoint;
    Point2D currentPoint;
    Point2D nextPoint = createPoint( 0, 0 );

    // Counts the amount of spaces in the matrix that doesn't have 'X' also assigns startingPoint and endPoint
    for ( x = 0; x < maze->length; x++)
    {
        for ( y = 0; y < maze->width; y++)
        {
            if ( maze->array2D[x][y] == 'S' )
            {
                startingPoint = createPoint( x, y );
            }
            if ( maze->array2D[x][y] == 'F')
            {
                endPoint = createPoint( x, y );
            }       
        } 
    }

    capacity = maze->length * maze->width;

    Graph* myGraph = createGraph( capacity );

    // Loops through matrix finding all vertex's edges until endPoint is found.
    for(x = 1; x < maze->length-1; x++ )
    {
        for( y = 1; y < maze->width-1; y++)
        {
            currentPoint.x = x;
            currentPoint.y = y;
            if ( maze->array2D[x+1][y] != 'X')
            {
                nextPoint.x = x+1;
                nextPoint.y = y;
                setEdge( myGraph, currentPoint, nextPoint, 0);
            }
            if (maze->array2D[x+1][y] == 'X')
            {
                nextPoint.x = x+1;
                nextPoint.y = y;
                setEdge( myGraph, currentPoint, nextPoint, 1);
            }
            if ( maze->array2D[x][y+1] != 'X')
            {
                nextPoint.x = x;
                nextPoint.y = y+1;
                setEdge( myGraph, currentPoint, nextPoint, 0);
            }
            if (maze->array2D[x][y+1] == 'X')
            {
                nextPoint.x = x;
                nextPoint.y = y+1;
                setEdge( myGraph, currentPoint, nextPoint, 1);
            }
            if ( maze->array2D[x-1][y] != 'X')
            {
                nextPoint.x = x-1;
                nextPoint.y = y;
                setEdge( myGraph, currentPoint, nextPoint, 0 );
            }
            if (maze->array2D[x-1][y] == 'X')
            {
                nextPoint.x = x-1;
                nextPoint.y = y;
                setEdge( myGraph, currentPoint, nextPoint, 1 );
            }
            if ( maze->array2D[x][y-1] == 'X')
            {
                nextPoint.x = x;
                nextPoint.y = y-1;
                setEdge( myGraph, currentPoint, nextPoint, 1 );
            }
            if ( maze->array2D[x][y-1] != 'X') 
            {
                nextPoint.x = x;
                nextPoint.y = y-1;
                setEdge( myGraph, currentPoint, nextPoint, 0 );
            }
        }
    }

    dijkstrasAlg( myGraph, startingPoint );

    distance = getDistance( myGraph, startingPoint, endPoint );

    freeGraph( myGraph );

    if (distance <= exploisives)
    {
        return PATH_FOUND;
    }
    return PATH_IMPOSSIBLE; /* TODO: Replace with PATH_FOUND or PATH_IMPOSSIBLE based on whether a path exists */
}
