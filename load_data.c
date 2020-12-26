#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "load_data.h"

#define NODES_PARAMS 3
#define EDGES_PARAMS 7

#define NODE_WKT_COLUMN 1
#define NODE_ID_COLUMN 2
#define NODE_NAME_COLUMN 3

#define EDGE_ID_COLUMN 6
#define EDGE_CNAME_COLUMN 4
#define EDGE_SOURCE_COLUMN 3
#define EDGE_TARGER_COLUMN 2
#define EDGE_LENGHT_COLUMN 1

station *load_nodes(char *file_path, int *n){
    if (!file_path){
        return 0;
    } 
    FILE* file = fopen(file_path, "r");

    station *nodes;
    char line[10000];
    int stop_line = 1;

    int nodes_count = 0;
    int max_id = 0;
    int l = 0;

    while (fgets(line, 10000, file))
    {
        int params_in_line = get_param_count(_strdup(line));
        char *tmp = _strdup(line);
        char *column = getfield(tmp, NODE_ID_COLUMN, ",");
        if (atoi(column) > max_id){
            max_id = atoi(column);
        }
    }

    fclose(file);
    file = fopen(file_path, "r");
    nodes = (station*)malloc(sizeof(station) * max_id);

    if (!nodes){
        return 0;
    }
    
    fgets(line, 10000, file);
    while (fgets(line, 10000, file))
    {        
        station temp_node;
        int i;
        for (i = 0; i <= NODES_PARAMS; i++){
            char *tmp = _strdup(line);
            char *column = getfield(tmp, i, ",");

            if (i == NODE_WKT_COLUMN){
                /*temp_node.position = line_to_point(column);*/
            }
            else if(i == NODE_ID_COLUMN){
                temp_node.id = atoi(column);
            }
            else if (i == NODE_NAME_COLUMN){
                if (!column){
                    strcpy(temp_node.name, "");
                }else{
                    strcpy(temp_node.name, column);
                }
            }
        }
        int j;
        int match = 0;
        for(j = 0; j <= nodes_count; j++){
            station tmp_n = nodes[j];
            if (tmp_n.id == temp_node.id){
                match = 1;
                break;
            }
        }

        if (match == 0){
            nodes[nodes_count] = temp_node;
            nodes_count++;
        }
        
        l++;
        /*
        stop_line++;
        if (stop_line == 1000){
            break;
        }*/
    }

    int a;

    *n = max_id; /*nodes_count*/;
    return nodes;
}


point line_to_point(char *line){
    if (!line){
        exit(EXIT_FAILURE);
    }

    double position_x, position_y;

    char *tmp = _strdup(line);

    char *column = getfield(tmp, 2, " ");
    column = getfield(column, 1, " ");
    column = getfield(column, 1, "(");
    position_y = atof(column);

    tmp = _strdup(line);
    column = getfield(tmp, 2, " ");
    column = getfield(column, 2, " ");
    column = getfield(column, 1, ")");
    position_x = atof(column);
    
    point position;
    position.position_x = position_x;
    position.position_y = position_y;

    return position;

}


int check_node_file(FILE *file){
    if (!file){
        return 0;
    }

    char line[10000];
    int stop_line = 1;
    int param_count = 0;

    while (fgets(line, 10000, file))
    {        
        int i;
        for (i = 1; i <= NODES_PARAMS; i++){
            char *tmp = _strdup(line);
            char *column = getfield(tmp, i, ",");
            if (strcmp("WKT", column) == 0|| strcmp("id", column) == 0 || strcmp("sname", column) == 0){
                param_count++;
            }

            free(tmp);
            free(column);
        }

        stop_line++;
        if (stop_line == 2){
            break;
        }
    }

    if (param_count == NODES_PARAMS){
        return 1;
    }
    else{
        return 0;
    }
}


char* getfield(char *line, int pos, char *delimiter)
{
    char *tok;
    for (tok = strtok(line, delimiter); tok && *tok; tok = strtok(NULL, ",\n")) {
        if (!--pos)
            return tok;
    }
    return NULL;
}


edge *load_edges(char *file_path, int *e){
    if (!file_path){
        return 0;
    } 
    FILE* file = fopen(file_path, "r");

    edge *edges;
    edge *temp_edge;
    temp_edge = (edge*)malloc(sizeof(edge));
    char line[10000];
    int stop_line = 1;

    int edges_count = 0;
    int max_id = 0;
    int l = 0;
    int params_in_line = get_param_count_edges(_strdup(line));
    int real_params = get_real_params(_strdup(line));
    int i;
    char *tmp;
    char *column;

    while (fgets(line, 10000, file))
    {
        int params_in_line = get_param_count(_strdup(line));
        char *tmp = _strdup(line);
        char *column = getfield(tmp, params_in_line-EDGE_ID_COLUMN, ",");
        if (atoi(column) > max_id){
            max_id = atoi(column);
        }
    }
    fclose(file);
    file = fopen(file_path, "r");
    edges = (edge*)malloc(sizeof(edge) * max_id);
    if (!edges){
        return 0;
    }
    
    fgets(line, 3000, file);
    while (fgets(line, 3000, file))
    {        
        
        temp_edge->id = 0;
        temp_edge->id_src = 0;
        temp_edge->id_dest = 0;
        temp_edge->weight = 0;

        params_in_line = get_param_count_edges(_strdup(line));
        real_params = get_real_params(_strdup(line));
        for (i = 1; i <= params_in_line; i++){
            tmp = _strdup(line);
            column = getfield(tmp, i, ",");
            
            if (real_params == 8){
                if (i == EDGE_LENGHT_COLUMN){
                temp_edge->weight = atof(column);
                }
                else if(i == params_in_line-EDGE_ID_COLUMN){
                    temp_edge->id = atoi(column);
                }
                else if (i == params_in_line-EDGE_SOURCE_COLUMN-1){
                    temp_edge->id_src = atoi(column);
                }
                else if (i == params_in_line-EDGE_TARGER_COLUMN-1){
                    temp_edge->id_dest = atoi(column);
                }
            }else{
                if (i == EDGE_LENGHT_COLUMN){
                temp_edge->weight = atof(column);
                }
                else if(i == params_in_line-EDGE_ID_COLUMN){
                    temp_edge->id = atoi(column);
                }
                else if (i == params_in_line-EDGE_SOURCE_COLUMN){
                    temp_edge->id_src = atoi(column);
                }
                else if (i == params_in_line-EDGE_TARGER_COLUMN){
                    temp_edge->id_dest = atoi(column);
                }
            }

            
        }
        
        int j;
        int bad = 0;
        for(j = 0; j <= edges_count; j++){
            edge tmp_n = edges[j];
            if ((tmp_n.id == temp_edge->id) || (temp_edge->id_src == temp_edge->id_dest)){
                bad = 1;
                break;
            }
        }

        if (bad == 0){
            /*printf("%d - (%d - %d) params: %d\n",temp_edge->id, temp_edge->id_src, temp_edge->id_dest, params_in_line);*/
            memcpy(&edges[edges_count],temp_edge,sizeof(edge));
            /*edges[temp_edge.id] = temp_edge;*/
            edges_count++;
        }
        
        l++;
        /*
        stop_line++;
        if (stop_line == 200){
            break;
        }*/
    }
    /*
    for (i = 0; i < 100; i++){
        printf("%d -> (%d , %d)\n", edges[i].id, edges[i].id_src, edges[i].id_dest);
    }*/
    free(temp_edge);
    *e = max_id /*edges_count*/;
    return edges;
}


int get_param_count(char *line)
{
    int i = 1;

    char *tmp = _strdup(line);
    char *tmp1 = _strdup(line);
    char *column = getfield(tmp, i, ",");
    char *column1 = getfield(tmp1, i+1, ",");

    while(1){
        if (column == NULL && column1 == NULL){
            break;
        }
        
        i++;
        tmp = _strdup(line);
        tmp1 = _strdup(line);
        column = getfield(tmp, i, ",");
        column1 = getfield(tmp1, i+1, ",");
    }
    if (i <= 8){
        return 8;
    }else{
        return i;
    }    
}

int get_param_count_edges(char *line)
{
    int i = 1;

    char *tmp = _strdup(line);
    char *tmp1 = _strdup(line);
    char *column = getfield(tmp, i, ",");
    char *column1 = getfield(tmp1, i+1, ",");

    while(1){
        if (column == NULL && column1 == NULL){
            break;
        }
        
        i++;
        tmp = _strdup(line);
        tmp1 = _strdup(line);
        column = getfield(tmp, i, ",");
        column1 = getfield(tmp1, i+1, ",");
    }

    if (i == 8){
        return 9;
    }else{
        return i;
    }  
}

int get_real_params(char *line)
{
    int i = 1;

    char *tmp = _strdup(line);
    char *tmp1 = _strdup(line);
    char *column = getfield(tmp, i, ",");
    char *column1 = getfield(tmp1, i+1, ",");

    while(1){
        if (column == NULL && column1 == NULL){
            break;
        }
        
        i++;
        tmp = _strdup(line);
        tmp1 = _strdup(line);
        column = getfield(tmp, i, ",");
        column1 = getfield(tmp1, i+1, ",");
    }

    return i;
}

int check_edge_file(FILE *file){
    if (!file){
        return 0;
    }

    char line[10000];
    int stop_line = 1;
    int param_count = 0;

    while (fgets(line, 10000, file))
    {        
        int i;
        for (i = 1; i <= EDGES_PARAMS; i++){
            char *tmp = _strdup(line);
            char *column = getfield(tmp, i, ",");
            if (strcmp("WKT", column) == 0|| strcmp("id", column) == 0 || strcmp("nation", column) == 0 
                || strcmp("cntryname", column) == 0 || strcmp("source", column) == 0 || strcmp("target", column) == 0 
                || strcmp("clength", column) == 0){
                param_count++;
            }

            free(tmp);
            free(column);
        }

        stop_line++;
        if (stop_line == 2){
            break;
        }
    }

    if (param_count == EDGES_PARAMS){
        return 1;
    }
    else{
        return 0;
    }
}