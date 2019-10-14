#include <iostream>

#include <libspu.hpp>
#include <structure.hpp>

using namespace std;
using namespace SPU;

#define INF    0xf
#define u_cnt  5 

/* Graph representation

       7
 '1' ------ '3' 
  |        /  \ 7
  |      /      \ 
 2|   4 /       '5'
  |   /         / 
  | /   1     / 6
 '2' ------ '4'

*/

/*************************************
  Structures definitions
*************************************/

/* Graph of convergence G */
Structure<void, string> G({ // Has data fields but not key fields
  { "Adj[u]", 16 }, // Has own Fields
  { "w[u]",   20 }, // Also has own Fields
  { "d[u]",   4  }, // Max distance is 15
  { "p[u]",   4  },
  { "u∈Q",    1  }, // Boolean
});
auto G_value = G.value();

/* Adj[u] fields */
Fields<> Adj_u({ // Every field is boolean
  { 1, 1 },
  { 2, 1 },
  { 3, 1 },
  { 4, 1 },
  { 5, 1 },
});

/* w[u] fields */
Fields<> w_u({ // Max distance is 16 
  { 1, 4 },
  { 2, 4 },
  { 3, 4 },
  { 4, 4 },
  { 5, 4 },
});

/* Structure of consideration Q */
Structure<string> Q({
  { "u",    8 },
  { "d[u]", 4 }, // d[u] is more important
});
auto Q_key = Q.key(); // Get Fields to separate Q key

/*************************************
  End of structures definitions
*************************************/

/* Helpers */
void G_init();
void Q_init();
void G_print();
void Q_print();

int main()
{
  cout << "Starting Dijkstra algorithm" << endl;

  /* G */
  G_init();
  G_print();

  /* Q */
  Q_init();
  Q_print();

  cout << "Starting" << endl;

  /*************************************
    Main algorithm
  *************************************/

  while(Q.get_power())
  {
    /* Get first node from Q and delete it */
    Q.min();
    u8 u = Q_key["u"]; // Index of node
    Q.del(Q_key);
    
    /* Get G_value from Q's "u" */
    G.search(u);
    Adj_u      = G_value["Adj[u]"];
    data_t d_u = G_value["d[u]"];

    /* Unset u∈Q */
    G_value["u∈Q"] = false;
    data_t u_value = G_value;

    /* Check out all v's from Adj[u] */
    for(auto ex : Adj_u)
    {
      /* If v in Adj[u] */
      if(ex.data)
      {
        /* Search for v */
        u8 v = ex.name;
        G.search(v); // Now G_value is value of v key
        w_u = G_value["w[u]"];

        /* v is in Q */
        if(G_value["u∈Q"])
        {
          /* Delete v from Q */
          Q_key["u"]    = v;
          Q_key["d[u]"] = G_value["d[u]"];
          Q.del(Q_key);

          /* Create new length statement */
          data_t len = d_u + w_u[u];
          if( G_value["d[u]"] > len )
          {
            /* Set new data */
            G_value["d[u]"] = len;
            G_value["p[u]"] = u;
            
            /* Save v state */
            G.insert(v, G_value);

            /* Insert new v in Q */
            Q_key["d[u]"] = G_value["d[u]"];
          }

          Q.insert(Q_key, 0);
        }
      }
    }

    /* Save u state */
    G.insert(u, u_value);

    G_print();
    Q_print();

    if (Q.get_power())
    {
      cout << "Turn" << endl;
    }
  }

  cout << "Ended" << endl;

  return 0;
}

/*************************************
  G initialization
*************************************/
void G_init()
{
  /* u = 1 */
  Adj_u  = { { 2, true }, { 3, true } };
  w_u    = { { 2, 2    }, { 3, 7    } };
  G.insert(1, {
    { "Adj[u]", Adj_u },
    { "w[u]",   w_u   },
    { "d[u]",   0     },
    { "p[u]",   0     },
    { "u∈Q",    true  } 
  });

  /* u = 2 */
  Adj_u  = { { 1, true }, { 3, true }, { 4, true } };
  w_u    = { { 1, 2    }, { 3, 4    }, { 4, 1    } };
  G.insert(2, {
    { "Adj[u]", Adj_u },
    { "w[u]",   w_u   },
    { "d[u]",   INF   },
    { "p[u]",   0     },
    { "u∈Q",    true  } 
  });

  /* u = 3 */
  Adj_u  = { { 1, true }, { 2, true }, { 4, true }, { 5, true } };
  w_u    = { { 1, 7    }, { 2, 4    }, { 4, 2    }, { 5, 7    } };
  G.insert(3, {
    { "Adj[u]", Adj_u },
    { "w[u]",   w_u   },
    { "d[u]",   INF   },
    { "p[u]",   0     },
    { "u∈Q",    true  } 
  });

  /* u = 4 */
  Adj_u  = { { 2, true }, { 3, true }, { 5, true } };
  w_u    = { { 2, 1    }, { 3, 2    }, { 5, 6    } };
  G.insert(4, {
    { "Adj[u]", Adj_u },
    { "w[u]",   w_u   },
    { "d[u]",   INF   },
    { "p[u]",   0     },
    { "u∈Q",    true  } 
  });

  /* u = 5 */
  Adj_u  = { { 3, true }, { 4, true } };
  w_u    = { { 3, 7    }, { 4, 6    } };
  G.insert(5, {
    { "Adj[u]", Adj_u },
    { "w[u]",   w_u   },
    { "d[u]",   INF   },
    { "p[u]",   0     },
    { "u∈Q",    true  } 
  });
}

/*************************************
  Q initialization
*************************************/
void Q_init()
{
  /* Q first node init */
  Q.insert(
    { { "d[u]", 0 },  { "u", 1 } },
    0
  );

  /* Q other nodes init */
  for(u8 u=2; u<=u_cnt; u++)
  {
    Q.insert(
      { { "d[u]", INF },  { "u", u } },
      0
    );
  }
}

/*************************************
  G printing
*************************************/
void G_print()
{
  /* Print out */
  cout << "G graph is:" << endl;
  for(u8 u=1; u<=u_cnt; u++)
  {
    pair_t pair =  G.search(u);
    cout << "\t u = " << to_string(pair.key) <<
      ":  " << to_string(pair.value, true) << endl;
  }

  cout << endl;
}

/*************************************
  Q printing
*************************************/
void Q_print()
{
  if (Q.get_power())
  {
    /* Print out */
    cout << "Q structures keys are:" << endl;

    /* First node */
    pair_t pair = Q.min();
    cout << "\t " << to_string(pair.key, true) << endl;

    /* Other nodes */
    for(u8 u=2; u<=Q.get_power(); u++)
    {
      pair = Q.next(pair.key);
      cout << "\t " << to_string(pair.key, true) << endl;
    }

    cout << endl;
  }
  else
  {
    cout << "Q is empty" << endl;
  }
}