package models

case class Student(index: Int, name: String, year: Short)
case class Lecture(id: String, name: String)
case class Enrollment(id: String, students: List[Student])

object DB {
  val students = List(
    Student(1, "Alice", 1),
    Student(2, "Bob", 1),
    Student(3, "Charlie", 2),
    Student(4, "Diana", 2),
    Student(5, "Eve", 3),
    Student(6, "Frank", 1),
    Student(7, "Grace", 2),
    Student(8, "Heidi", 3),
    Student(9, "Ivan", 1),
    Student(10, "Judy", 3)
  )

  val lectures = List(
    Lecture("SIP", "Scala in Practice"),
    Lecture("HDK", "hakowanie dla kazdego"),
    Lecture("PPW", "Programowanie pod Windows"),
    Lecture("SI", "Sztuczna Inteligencja")
  )

  val enrollments = List(
    Enrollment("SIP", students.take(5)),
    Enrollment("HDK", students.slice(3, 8)),
    Enrollment("PPW", students.slice(5, 10)),
    Enrollment("SI", students.slice(2, 6))
  )

  def getStudent(index: Int): Option[Student] =
    students.find(_.index == index)

  def getLecture(id: String): Option[Lecture] =
    lectures.find(_.id == id)

  def getEnrolledStudents(lectureId: String): List[Student] =
    enrollments.find(_.id == lectureId).map(_.students).getOrElse(List())
}
