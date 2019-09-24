#include "mu_test.h"
#include "Vertex.h"
#include "Graph.h"


UNIT(create_graph)
    
    Vertex<std::string> v("hey");
    Vertex<std::string> v1("what");
    Vertex<std::string> v2("who");
    Vertex<std::string> v3("where");
    Vertex<std::string> v4("when");
    Graph<int, Vertex<std::string> > g(true,false);
    
    g.add(v);
    g.add(v1);
    g.add(v2);
    /* g.add(v3);
    g.add(v4); */
    g.connect(v,v1,20);
    g.connect(v,v2,10);   
    //g.connect(v1,v2,30);   
    g.primAlgorithem();
   /*  g.connect(v1,v3,30);   
    g.connect(v3,v4,40);   
      

    ASSERT_EQUAL(true, g.isNeighbors(v,v1)); 
    ASSERT_EQUAL(true, g.isNeighbors(v1,v2)); 
    ASSERT_EQUAL(false, g.isNeighbors(v,v2)); 
    ASSERT_EQUAL(false, g.isNeighbors(v2,v)); 

    ASSERT_EQUAL(true,g.isConnected(v,v2));
    ASSERT_EQUAL(true,g.isConnected(v,v3));
    ASSERT_EQUAL(true,g.isConnected(v,v4));
    ASSERT_EQUAL(true,g.isConnected(v1,v));
   

    g.disconnect(v1,v2);
    ASSERT_EQUAL(true, g.isNeighbors(v,v1)); 
    ASSERT_EQUAL(false, g.isNeighbors(v1,v2)); 
    ASSERT_EQUAL(false, g.isNeighbors(v2,v1));  */


END_UNIT



TEST_SUITE(Graph Test)

    TEST(create_graph)

END_SUITE