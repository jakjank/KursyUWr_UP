object Utils{
    def isSorted(as: List[Int], ordering: (Int, Int) => Boolean) = 
        (0 until as.length-1).forall(i => ordering(as(i), as(i + 1)))

    def isAscSorted(as: List[Int]) = 
        isSorted(as, (a,b) => a<b)

    def isDescSorted(as: List[Int]) =
        isSorted(as, (a,b) => a>b)

    def foldLeft[A, B](l: List[A], z: B)(f: (B, A) => B): B = 
        if(l.nonEmpty){
            foldLeft(l.tail, f(z,l(0)))(f)
        } else{
            z
        }

    def sum(l: List[Int]) = foldLeft(List(1,2,3,4), 0)((a,b) => a+b)

    def length[A](l: List[A]) = Utils.foldLeft(List(1,2,3,4), 0)((a,b) => a+1)

    def compose[A, B, C](f: B => C, g: A => B ) : A=>C =
        x => f(g(x))

    def repeated[A, B](f: A => A, n: Int) : A => A =
        if (n==1) f else compose(f, repeated(f, n-1))
        
    def curry[A, B, C](f: (A,B) => C) =
        // (x: A) => f(x,_) ok???
        (x: A) => (y: B) => f(x,y)

    def uncurry[A, B, C](f: A => B => C) =
        (x: A, y: B) => f(x)(y)
}

@main
def main() = 
    // println(Utils.isSorted(List(1,2,3,4), (a,b) => a<b))
    // println(Utils.isSorted(List(1,3,2,4), (a,b) => a<b))

    // println(Utils.isAscSorted(List(1,2,3)))
    // println(Utils.isAscSorted(List(1,3,2)))

    // println(Utils.isDescSorted(List(3,2,1)))
    // println(Utils.isDescSorted(List(1,2,3)))

    // println(Utils.foldLeft(List(1,2,3,4), 0)((a,b) => a+b))
    // println(Utils.foldLeft(List(1,2,3,4), 0)((a,b) => a+1))

    // println(Utils.compose((x: Int) => x.toString , (y: Int) => 3 + y)(2))

    println(Utils.repeated((x: Int) => x*2, 3)(1))

    // def myFun = (a:Int,b:Int) => a+b
    // println(myFun(4,3))

    // def myFun2 = Utils.curry(myFun)
    // println(myFun2(3)(4))
    
    // println(Utils.uncurry(myFun2)(4, 3))


