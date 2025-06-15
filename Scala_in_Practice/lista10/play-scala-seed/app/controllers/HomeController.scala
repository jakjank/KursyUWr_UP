package controllers

import javax.inject._
import play.api._
import play.api.mvc._

import models._

/**
 * This controller creates an `Action` to handle HTTP requests to the
 * application's home page.
 */
@Singleton
class HomeController @Inject()(val controllerComponents: ControllerComponents) extends BaseController {

  /**
   * Create an Action to render an HTML page.
   *
   * The configuration in the `routes` file means that this method
   * will be called when the application receives a `GET` request with
   * a path of `/`.
   */
  def index() = Action { implicit request: Request[AnyContent] =>
    Ok(views.html.students(DB.students))
  }

  def students = Action {
    Ok(views.html.students(DB.students))
  }

  def student(index: Int) = Action {
    DB.getStudent(index) match {
      case Some(s) => Ok(views.html.student(s))
      case None    => NotFound("Student not found")
    }
  }

  def lectures = Action {
    Ok(views.html.lectures(DB.lectures))
  }

  def lecture(id: String) = Action {
    DB.getLecture(id) match {
      case Some(l) =>
        val students = DB.getEnrolledStudents(id)
        Ok(views.html.lecture(l, students))
      case None => NotFound("Lecture not found")
    }
  }
}
