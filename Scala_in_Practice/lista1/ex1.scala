import scala.util.Random

def scalarUgly(xs: List[Int], ys: List[Int]) : Int =
    var sum = 0
    var i = 0
    while(i < xs.length)
        sum += xs(i) * ys(i)
        i += 1
    sum

def scalar(xs: List[Int], ys: List[Int]) : Int =
    (for ((x,y) <- xs.zip(ys)) yield x*y).sum

def sortUgly(xs: List[Int]): List[Int] =
    if (xs.length <=1){
        xs
    } else{
        var left = List[Int]()
        var right = List[Int]()
        val pivot = xs(Random.nextInt(xs.length))
        var i=0
        while(i < xs.length){
            //println(xs(i))
            if(xs(i) < pivot){
                left = xs(i) :: left
            } else{
                right = xs(i) :: right
            }
            i += 1
        }
        //print("sorting: ", left, right)
        sortUgly(left) ::: sortUgly(right)
    }

def sort(xs: List[Int]): List[Int] =
    if (xs.length <=1){
        xs
    } else {
        val pivot = xs(Random.nextInt(xs.length))
        val (left,right) = xs.partition(_ < pivot)
        sort(left) ::: sort(right)
    }

def isPrimeUgly(n: Int): Boolean = 
    var i = 2
    while (i*i < n){
        if(n%i == 0) return false
        i += 1
    }
    true

def isPrime(n: Int): Boolean =
    (2 until math.sqrt(n).toInt + 1).forall(n % _ != 0)

def primePairsUgly(n : Int): List[(Int, Int)] =
    var result = List[((Int),(Int))]()
    for(i <- 1.to(n) ; j <- (i+1).to(n)){
        println(i)
        println(j)
        if(isPrime(i+j)){
            result = (i,j) :: result
        }
    }
    result.reverse // just so primesPairs looks the same

def primePairs(n : Int): List[(Int, Int)] =
    (for{
        i <- 1.to(n)
        j <- (i+1).to(n)
        if(isPrime(i+j))
    } yield (i,j)).toList

val filesHere = new java.io.File(".").listFiles

def fileLinesUgly(file: java.io.File): List[String] =
    val lines = scala.io.Source.fromFile(file).getLines() //.toList
    var result = List[String]()
    while (lines.hasNext) {
        result = lines.next() :: result
    }
    result.reverse


def fileLines(file: java.io.File): List[String] =
    scala.io.Source.fromFile(file).getLines().toList

def printNonEmptyUgly(pattern: String): Unit =
    for(file <- filesHere){
        if(!file.isDirectory && file.getName.endsWith(pattern)){
            if (fileLinesUgly(file).nonEmpty) println(file.getName)
        }
    }

def printNonEmpty(pattern: String): Unit =
    for {
    file <- filesHere
    if !file.isDirectory
    if file.getName.endsWith(pattern)
    if fileLines(file).nonEmpty
  } println(file.getName)

@main
def run() =
    // println(scalarUgly(List(1,2,3), List(3,4,5)))
    // println(scalar(List(1,2,3), List(3,4,5)))

    // println(sortUgly(List(1,6,4,2,9,8,3,7,5)))
    // println(sort(List(1,6,4,2,9,8,3,7,5)))

    // println(isPrimeUgly(139))
    // println(isPrime(143))

    // println(primePairsUgly(5))
    // println(primePairs(5))

    // for(line <- fileLinesUgly(filesHere(1))) println(line)
    // for(line <- fileLines(filesHere(1))) println(line)

    // printNonEmptyUgly(".scala")
    // printNonEmpty(".scala")
    