import os
import pickle

class Student:
    def __init__(self, student_id, name, age, grade):
        self.student_id = student_id
        self.name = name
        self.age = age
        self.grade = grade

    def __str__(self):
        return f"ID: {self.student_id}, Name: {self.name}, Age: {self.age}, Grade: {self.grade}"

class StudentManagementSystem:
    def __init__(self, filename="students.dat"):
        self.filename = filename
        self.students = self.load_data()

    def load_data(self):
        if os.path.exists(self.filename):
            with open(self.filename, "rb") as file:
                return pickle.load(file)
        return {}

    def save_data(self):
        with open(self.filename, "wb") as file:
            pickle.dump(self.students, file)

    def add_student(self):
        student_id = input("Enter student ID: ")
        if student_id in self.students:
            print("Student ID already exists.")
            return
        name = input("Enter student name: ")
        age = int(input("Enter student age: "))
        grade = input("Enter student grade: ")
        student = Student(student_id, name, age, grade)
        self.students[student_id] = student
        self.save_data()
        print("Student added successfully.")

    def view_student(self):
        student_id = input("Enter student ID: ")
        student = self.students.get(student_id)
        if student:
            print(student)
        else:
            print("Student not found.")

    def update_student(self):
        student_id = input("Enter student ID: ")
        student = self.students.get(student_id)
        if student:
            name = input(f"Enter new name (current: {student.name}): ")
            age = int(input(f"Enter new age (current: {student.age}): "))
            grade = input(f"Enter new grade (current: {student.grade}): ")
            student.name = name
            student.age = age
            student.grade = grade
            self.save_data()
            print("Student updated successfully.")
        else:
            print("Student not found.")

    def delete_student(self):
        student_id = input("Enter student ID: ")
        if student_id in self.students:
            del self.students[student_id]
            self.save_data()
            print("Student deleted successfully.")
        else:
            print("Student not found.")

    def list_students(self):
        if self.students:
            for student in self.students.values():
                print(student)
        else:
            print("No students available.")

    def menu(self):
        while True:
            print("\nStudent Management System")
            print("1. Add Student")
            print("2. View Student")
            print("3. Update Student")
            print("4. Delete Student")
            print("5. List All Students")
            print("6. Exit")
            choice = input("Enter your choice: ")
            if choice == "1":
                self.add_student()
            elif choice == "2":
                self.view_student()
            elif choice == "3":
                self.update_student()
            elif choice == "4":
                self.delete_student()
            elif choice == "5":
                self.list_students()
            elif choice == "6":
                print("Exiting...")
                break
            else:
                print("Invalid choice. Please try again.")

if __name__ == "__main__":
    system = StudentManagementSystem()
    system.menu()

