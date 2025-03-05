#include <bits/stdc++.h>
#include <algorithm>
#include <vector>
#include <cmath>
// JESZCZE SZYBKIE LINIJKI

using namespace std;

class Point
{
    public:
    int x;
    int y;

    Point(int a, int b){
        x = a;
        y = b;
    }

    Point(){
        x = 0;
        y = 0;
    }

    void setter(int a, int b){
        x=a;
        y=b;
    }

    friend ostream& operator<<(std::ostream& out, Point& a)
    {
    string wyn = "";
    wyn += "(" + to_string(a.x) + ", "+ to_string(a.y) + ")"; 

    return out << wyn;
    }
};

Point A,B,C; //punkty wynikowe
double min_peri = 1e30;

bool x_compare(Point A, Point B){
    return A.x < B.x;
}

bool y_compare(Point A, Point B){
    return A.y <B.y;
}

long long power(int a, int b){
    return (long long)(a-b)*(long long)(a-b);
}

double dist(Point a, Point b){
    return sqrt((double)(power(a.x,b.x)+power(a.y,b.y)));
}

double perimeter(Point a, Point b, Point c){
    return dist(a,b)+dist(b,c)+dist(c,a);
}

void bruteforce(vector<Point>& points){
    int n = points.size();
    double peri;
    Point p1,p2,p3;
    for(int i=0;i<n-2;i++){
        for(int j=i+1;j<n-1;j++){
            for(int k=j+1;k<n;k++){
                peri = perimeter(points[i],points[j],points[k]);
                if(peri<min_peri){
                    min_peri = peri;
                    A = points[i];
                    B = points[j];
                    C = points[k];
                }
            }
        }
    }
}

void calc_near_line(vector<Point>& points){
    if(points.size()<3){
        return;
    }
    sort(points.begin(), points.end(), y_compare);
    double peri;
    for(int i = 0; i<points.size()-2; i++){
        if(points[i].y - points[i+2].y > min_peri){
            continue;
        }
        peri = perimeter(points[i],points[i+1],points[i+2]);
        if(peri<min_peri){
            min_peri = peri;
            A = points[i];
            B = points[i+1];
            C = points[i+2];
        }
    }
}

void d_and_c(vector<Point>& points){
    if(points.size()<10){
        bruteforce(points);
    }
    else{
        int m = points.size()/2;
        int line = points[m].x;

        vector<Point>::const_iterator first1 = points.begin();
        vector<Point>::const_iterator last1 = points.begin() + m;
        vector<Point>::const_iterator first2 = points.begin() + m+1;
        vector<Point>::const_iterator last2 = points.end();
        vector<Point> sub_vec1(first1, last1);
        vector<Point> sub_vec2(first2, last2);
        d_and_c(sub_vec1);
        d_and_c(sub_vec2);

        vector<Point> near_line;
        //reserve
        for(Point el: points){
            if(abs(el.x - line) <= min_peri/2){
                near_line.push_back(el);
            }
        }
        calc_near_line(near_line);
    }   
}

void prepare(vector<Point>& points){
    sort(points.begin(), points.end(), x_compare);
    d_and_c(points);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,a,b;
    cin>>n;
    vector<Point> points;
    points.reserve(n+1);

    for(int i=0;i<n;i++){
        cin>>a>>b;
        points.push_back(Point(a,b));
    }

    if(n < 10){
        bruteforce(points);
    }
    else{
        prepare(points);
    }

    cout<<A.x<<" "<<A.y<<"\n"<<
          B.x<<" "<<B.y<<"\n"<<
          C.x<<" "<<C.y;
    return 0;
}