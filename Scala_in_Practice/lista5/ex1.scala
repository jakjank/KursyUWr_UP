import plugins.Actions._

object MyApp extends App {
  val input = "Hello  World!"

  println(s"Action A: ${actionA.plugin(input)}")
  println(s"Action B: ${actionB.plugin(input)}")
  println(s"Action C: ${actionC.plugin(input)}")
  println(s"Action D: ${actionD.plugin(input)}")
}