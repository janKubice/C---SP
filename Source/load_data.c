#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Headers/load_data.h"

#define NODES_PARAMS 3
#define EDGES_PARAMS 7

#define NODE_WKT_COLUMN 1
#define NODE_ID_COLUMN 2
#define NODE_NAME_COLUMN 3

#define EDGE_ID_COLUMN 6
#define EDGE_COUNTRY_ID 5
#define EDGE_CNAME_COLUMN 4
#define EDGE_SOURCE_COLUMN 3
#define EDGE_TARGER_COLUMN 2
#define EDGE_LENGHT_COLUMN 1

station *load_nodes(char *file_path, int *n)
{
    if (!file_path || !n)
    {
        return 0;
    }
    FILE *file = fopen(file_path, "r");

    station *nodes;
    char line[10000];
    int nodes_count = 0;
    int nodes_loaded = 0;
    int stop_line = 0;
    while (fgets(line, 10000, file))
    {
        nodes_count++;
    }

    rewind(file);
    nodes = (station *)malloc(sizeof(station) * nodes_count+1);

    if (!nodes)
    {
        return 0;
    }
    
    fgets(line, 10000, file);
    while (fgets(line, 10000, file))
    {
        station temp_node;
        int i;
        for (i = 0; i <= NODES_PARAMS; ++i)
        {
            char *tmp = _strdup(line);
            char *column = getfield(tmp, i, ",");

            if (i == NODE_ID_COLUMN)
            {
                temp_node.id = atoi(column);
            }
            else if (i == NODE_WKT_COLUMN){
                temp_node.pos_y = extract_pos(column,1);

                tmp = _strdup(line);
                column = getfield(tmp, i, ",");

                temp_node.pos_x = extract_pos(column,2);
            }
            else if (i == NODE_NAME_COLUMN)
            {
                if (!column)
                {
                    strcpy(temp_node.name, "");
                }
                else
                {
                    strcpy(temp_node.name, column);
                }
            }

            free(tmp);
            free(column);
        }
        int j;
        int match = 0;

        for (j = 0; j <= nodes_loaded; j++)
        {
            station tmp_n = nodes[j];
            if (tmp_n.id == temp_node.id)
            {
                match = 1;
                break;
            }
        }

        if (match == 0)
        {
            nodes[nodes_loaded] = temp_node;
            nodes_loaded++;
        }
        
    }
    *n = nodes_loaded;
    return nodes;
}

float extract_pos(char *line, int pos){
    char *tmp = _strdup(line);
    char *column = getfield(tmp, 2, "(");

    column = getfield(column, 1, ")");
    column = getfield(column, pos, " ");

    return atof(column);
}

char *line_to_point(char *line, int params)
{
    if (!line || params == NULL || params < 0)
    {
        exit(EXIT_FAILURE);
    }
    return _strdup(line);
}

int check_node_file(FILE *file)
{
    if (!file)
    {
        return 0;
    }

    char line[10000];
    int stop_line = 1;
    int param_count = 0;

    while (fgets(line, 10000, file))
    {
        int i;
        for (i = 1; i <= NODES_PARAMS; i++)
        {
            char *tmp = _strdup(line);
            char *column = getfield(tmp, i, ",");
            if (strcmp("WKT", column) == 0 || strcmp("id", column) == 0 || strcmp("sname", column) == 0)
            {
                param_count++;
            }

            free(tmp);
            free(column);
        }

        stop_line++;
        if (stop_line == 2)
        {
            break;
        }
    }

    if (param_count == NODES_PARAMS)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

char *getfield(char *line, int pos, char *delimiter)
{
    char *tok;
    for (tok = strtok(line, delimiter); tok && *tok; tok = strtok(NULL, ",\n"))
    {
        if (!--pos)
            return tok;
    }
    return NULL;
}

edge *load_edges(char *file_path, int *e)
{
    if (!file_path)
    {
        return 0;
    }
    FILE *file = fopen(file_path, "r");

    edge *edges;
    edge temp_edge;
    char line[15000];

    int edges_count = 0;
    int edges_lines = 0;
    int params_in_line = get_param_count_edges(_strdup(line));
    int real_params = get_real_params(_strdup(line));
    int i;
    char *tmp;
    char *column;
    edge *tmp_n;
    int j;
    int bad = 0;
    
    while (fgets(line, 12000, file))
    {
        edges_lines++;
    }
    rewind(file);
    edges = (edge *)malloc(sizeof(edge) * edges_lines+1);
    if (!edges)
    {
        return 0;
    }

    for (i = 0; i < edges_lines; i++)
    {
        edges[i].id = 0;
    }
    float total_w = 0;
    fgets(line, 12000, file);
    while (fgets(line, 12000, file))
    {

        temp_edge.id = 0;
        temp_edge.id_src = 0;
        temp_edge.id_dest = 0;
        temp_edge.weight = 0;
        temp_edge.nation_id = 0;
        strcpy(temp_edge.nation_name, "");

        params_in_line = get_param_count_edges(_strdup(line));
        real_params = get_real_params(_strdup(line));

        tmp = _strdup(line);
        column = getfield(tmp, 1, ")");
        /*strcpy(temp_edge->pos,line_to_point(column, params_in_line));*/
        strcpy(temp_edge.pos, _strdup(column));
        for (i = 1; i <= params_in_line; ++i)
        {
            tmp = _strdup(line);
            column = getfield(tmp, i, ",");

            if (real_params == 8)
            {
                if (i == params_in_line - 2)
                {
                    temp_edge.weight = atof(column);
                }
                else if (i == params_in_line - EDGE_ID_COLUMN)
                {
                    temp_edge.id = atoi(column);
                }
                else if (i == params_in_line - EDGE_SOURCE_COLUMN - 1)
                {
                    temp_edge.id_src = atoi(column);
                }
                else if (i == params_in_line - EDGE_TARGER_COLUMN - 1)
                {
                    temp_edge.id_dest = atoi(column);
                }
                else if (i == params_in_line - EDGE_CNAME_COLUMN)
                {
                    strcpy(temp_edge.nation_name, column);
                }
                else if (i == params_in_line - EDGE_COUNTRY_ID - 1)
                {
                    temp_edge.nation_id = atoi(column);
                }
            }
            else
            {
                if (i == params_in_line - 1)
                {
                    temp_edge.weight = atof(column);
                }
                else if (i == params_in_line - EDGE_ID_COLUMN)
                {
                    temp_edge.id = atoi(column);
                }
                else if (i == params_in_line - EDGE_SOURCE_COLUMN)
                {
                    temp_edge.id_src = atoi(column);
                }
                else if (i == params_in_line - EDGE_TARGER_COLUMN)
                {
                    temp_edge.id_dest = atoi(column);
                }
                else if (i == params_in_line - EDGE_CNAME_COLUMN)
                {
                    strcpy(temp_edge.nation_name, column);
                }
                else if (i == params_in_line - EDGE_COUNTRY_ID)
                {
                    temp_edge.nation_id = atoi(column);
                }
            }

            
        }

        bad = 0;
        for (j = 0; j <= edges_count; j++)
        {
            tmp_n = &edges[j];
            if ((tmp_n->id == temp_edge.id) || (temp_edge.id_src == temp_edge.id_dest) || (tmp_n->id_src == temp_edge.id_src && tmp_n->id_dest == temp_edge.id_dest))
            {
                bad = 1;
                break;
            }
        }
        tmp_n = NULL;
        if (bad == 0){
            edges[edges_count] = temp_edge;
            edges_count++;
        }

        free(tmp);
        free(column);
        tmp = NULL;
        column = NULL;
    }
    *e = edges_count;
    return edges;
}

int get_param_count(char *line)
{
    int i = 1;

    char *tmp = _strdup(line);
    char *tmp1 = _strdup(line);
    char *column = getfield(tmp, i, ",");
    char *column1 = getfield(tmp1, i + 1, ",");

    while (1)
    {
        if (column == NULL && column1 == NULL)
        {
            break;
        }

        free(tmp);
        free(tmp1);

        i++;
        tmp = _strdup(line);
        tmp1 = _strdup(line);
        column = getfield(tmp, i, ",");
        column1 = getfield(tmp1, i + 1, ",");
    }

    if (i <= 8)
    {
        return 8;
    }
    else
    {
        return i;
    }
}

int get_param_count_edges(char *line)
{
    int i = 1;

    char *tmp = _strdup(line);
    char *tmp1 = _strdup(line);
    char *column = getfield(tmp, i, ",");
    char *column1 = getfield(tmp1, i + 1, ",");

    while (1)
    {
        if (column == NULL && column1 == NULL)
        {
            break;
        }

        i++;

        free(tmp);
        free(tmp1);

        tmp = _strdup(line);
        tmp1 = _strdup(line);
        column = getfield(tmp, i, ",");
        column1 = getfield(tmp1, i + 1, ",");
    }


    if (i == 8)
    {
        return 9;
    }
    else
    {
        return i;
    }
}

int get_real_params(char *line)
{
    int i = 1;

    char *tmp = _strdup(line);
    char *tmp1 = _strdup(line);
    char *column = getfield(tmp, i, ",");
    char *column1 = getfield(tmp1, i + 1, ",");

    while (1)
    {
        if (column == NULL && column1 == NULL)
        {
            break;
        }

        free(tmp);
        free(tmp1);

        i++;
        tmp = _strdup(line);
        tmp1 = _strdup(line);
        column = getfield(tmp, i, ",");
        column1 = getfield(tmp1, i + 1, ",");
    }



    return i;
}

int check_edge_file(FILE *file)
{
    if (!file)
    {
        return 0;
    }

    char line[10000];
    int stop_line = 1;
    int param_count = 0;

    while (fgets(line, 10000, file))
    {
        int i;
        for (i = 1; i <= EDGES_PARAMS; i++)
        {
            char *tmp = _strdup(line);
            char *column = getfield(tmp, i, ",");
            if (strcmp("WKT", column) == 0 || strcmp("id", column) == 0 || strcmp("nation", column) == 0 || strcmp("cntryname", column) == 0 || strcmp("source", column) == 0 || strcmp("target", column) == 0 || strcmp("clength", column) == 0)
            {
                param_count++;
            }

            free(tmp);
            free(column);
        }

        stop_line++;
        if (stop_line == 2)
        {
            break;
        }
    }

    if (param_count == EDGES_PARAMS)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}