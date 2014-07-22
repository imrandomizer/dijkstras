#include<stdio.h>
#include<string.h>
#include<iostream>
#include<vector>
#define INF 1<<31-1

using namespace std;

class min_heap{
    //can also be implemented by make_heap(v.begin(), v.end(), comp);
    int leaf;
    vector <pair<int,int>> arr;//<weight,vertex>
public:

    min_heap(){
        leaf=1;
        arr.push_back(make_pair(0,0));
    }
    void push(int weight,int node){
        int pvt=leaf;
        if(arr.size()<=pvt)
            arr.push_back(make_pair(weight,node));
        else
            arr[pvt]=make_pair(weight,node);


        while(pvt>1){
            if(arr[pvt].first<arr[pvt/2].first){
                swap(arr[pvt],arr[pvt/2]);
                pvt=pvt/2;
            }
            else
                break;
        }
        leaf++;
    }

    int pop(){
        int ans=arr[1].second;
        arr[1]=arr[leaf-1];
        int elm=arr[1].first,x=1;
        while(x*2+1<=leaf-1){
            int exc=1,temp=arr[x].first;

            //exchanging parent with the child with smaller value
            if(arr[x*2].first>arr[x*2+1].first && (elm>arr[x*2].first || elm>arr[x*2+1].first )){
                swap(arr[x],arr[x*2+1]);
                x=x*2+1;
                continue;
            }
            if(arr[x*2].first<=arr[x*2+1].first && (elm>arr[x*2].first || elm>arr[x*2+1].first)){
                swap(arr[x],arr[x*2]);
                x=x*2;
                continue;
            }
            break;

        }
        if(leaf-1>=x*2  &&  arr[x*2].first<arr[x].first ){
            swap(arr[x],arr[x*2]);
        }
        leaf--;
        return ans;
    }
    bool isempty(){
        if(leaf<=1)
            return true;
        return false;
    }
};

class dijkstra{
public:
    vector <int> visited;//to mark if a vertex has been visited
    vector <int> weight;//Current minimum weight to n'th node from source
    vector <int> previous;//to store shortest path information

    min_heap heap;
    bool calculated;
    int vertex;
//public:
    dijkstra(int vertex_cnt){

        visited.resize(vertex_cnt+1,0);
        weight.resize(vertex_cnt+1,INF);
        previous.resize(vertex_cnt+1,INF);

        calculated=false;
        vertex=vertex_cnt;
    }
    // graph[i][0] contains the no of edges to i'th vertex
    // graph[i][1...graph[i][0]] contains the vertex information connected to i'th vertex
    // information structure <weight,vertex>
    int shortest_path(vector <vector<pair<int,int>>> graph,int first_node,int end_node){
        weight[first_node]=0;
        heap.push(first_node,first_node);

        while(heap.isempty()==false){
            int p_vertex=heap.pop();


            for(int i=1;i<=graph[p_vertex][0].first;i++){

                int new_vertex=graph[p_vertex][i].second;//
                int new_weight=weight[p_vertex]+graph[p_vertex][i].first;

                if(visited[new_vertex]==0){
                    heap.push(new_weight,new_vertex);

                    if(new_weight<weight[new_vertex])
                        previous[new_vertex]=p_vertex;//updating path if a path with less weight is found

                    weight[new_vertex]=min(weight[new_vertex],new_weight);//update

                }
            }
            visited[p_vertex]=1;
            if(p_vertex==end_node){
                calculated=true;
                return weight[end_node];
            }
        }

        return INF;

    }
    //to return the actual shortest path taken in reverse 
    void shortest_path(vector <int> &act_path,int source,int destination){
        if(calculated=false)
            return;
        act_path.push_back(destination);
        while(destination!=source){
            act_path.push_back(previous[destination]);
            destination=previous[destination];
        }
    }


};
/*
format of graph is an adjacency list implemented through a vector or vectors 
the first element of the vector contains number of edges adjacent to a node 
*/


int main()
{

    vector <vector<pair<int,int>>> graph1;//A vector of vector list to contain adjacency list
    graph1.push_back(vector<pair<int,int>> (1,make_pair(0,0)));

    int N;
    cin>>N;//number of vertex
    for(int i=1;i<=N;i++){
        int E;
        cin>>E;//number of vertex to which i'th vertex is connected
        vector <pair<int,int>> info;
        info.push_back(make_pair(E,0));
        for(int j=1;j<=E;j++){
            
            int vtx,weight;
            cin>>vtx>>weight;//vertex connection and weight of that edge
            info.push_back(make_pair(weight,vtx));
            
        }
        graph1.push_back(info);
    }
    
    int source,destination;
    cin>>source>>destination;//destination

    dijkstra short1(N);
    cout<<"shortest distance ="<<short1.shortest_path(graph1,source,destination);

    vector <int> path1;//to store actual path in reverse
    short1.shortest_path(path1,source,destination);
    for(int i=0;i<path1.size();i++)
        cout<<path1[i]<<endl;

}
