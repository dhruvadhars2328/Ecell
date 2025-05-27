// Task class to represent a single task
class Task {
    constructor(id, title, description, dueDate, priority) {
        this.id = id;
        this.title = title;
        this.description = description;
        this.dueDate = dueDate;
        this.priority = priority;
        this.completed = false;
    }

    toggleCompletion() {
        this.completed = !this.completed;
    }

    updateDetails(title, description, dueDate, priority) {
        this.title = title;
        this.description = description;
        this.dueDate = dueDate;
        this.priority = priority;
    }
}

// TaskManager class to handle task operations
class TaskManager {
    constructor() {
        this.tasks = [];
    }

    addTask(title, description, dueDate, priority) {
        const id = this.tasks.length + 1;
        const newTask = new Task(id, title, description, dueDate, priority);
        this.tasks.push(newTask);
        return newTask;
    }

    removeTask(id) {
        const index = this.tasks.findIndex(task => task.id === id);
        if (index !== -1) {
            this.tasks.splice(index, 1);
            return true;
        }
        return false;
    }

    getTask(id) {
        return this.tasks.find(task => task.id === id);
    }

    getAllTasks() {
        return this.tasks;
    }

    getIncompleteTasks() {
        return this.tasks.filter(task => !task.completed);
    }

    getCompletedTasks() {
        return this.tasks.filter(task => task.completed);
    }

    updateTask(id, title, description, dueDate, priority) {
        const task = this.getTask(id);
        if (task) {
            task.updateDetails(title, description, dueDate, priority);
            return task;
        }
        return null;
    }

    toggleTaskCompletion(id) {
        const task = this.getTask(id);
        if (task) {
            task.toggleCompletion();
            return task;
        }
        return null;
    }
}

// DOM Manipulation for Task Management UI
class TaskUI {
    constructor(taskManager) {
        this.taskManager = taskManager;
        this.taskList = document.getElementById('task-list');
        this.taskForm = document.getElementById('task-form');
        this.titleInput = document.getElementById('title');
        this.descriptionInput = document.getElementById('description');
        this.dueDateInput = document.getElementById('due-date');
        this.priorityInput = document.getElementById('priority');
        this.submitButton = document.getElementById('submit');
        this.editingTask = null;

        this.submitButton.addEventListener('click', (e) => this.handleSubmit(e));
        this.renderTasks();
    }

    renderTasks() {
        this.taskList.innerHTML = '';
        const tasks = this.taskManager.getAllTasks();
        tasks.forEach(task => {
            const taskElement = this.createTaskElement(task);
            this.taskList.appendChild(taskElement);
        });
    }

    createTaskElement(task) {
        const taskElement = document.createElement('li');
        taskElement.classList.add('task');
        taskElement.dataset.id = task.id;

        const title = document.createElement('h3');
        title.textContent = task.title;
        taskElement.appendChild(title);

        const description = document.createElement('p');
        description.textContent = task.description;
        taskElement.appendChild(description);

        const dueDate = document.createElement('p');
        dueDate.textContent = `Due: ${task.dueDate}`;
        taskElement.appendChild(dueDate);

        const priority = document.createElement('p');
        priority.textContent = `Priority: ${task.priority}`;
        taskElement.appendChild(priority);

        const actions = document.createElement('div');
        actions.classList.add('actions');

        const toggleButton = document.createElement('button');
        toggleButton.textContent = task.completed ? 'Mark Incomplete' : 'Mark Complete';
        toggleButton.addEventListener('click', () => this.toggleTaskCompletion(task.id));
        actions.appendChild(toggleButton);

        const editButton = document.createElement('button');
        editButton.textContent = 'Edit';
        editButton.addEventListener('click', () => this.editTask(task.id));
        actions.appendChild(editButton);

        const deleteButton = document.createElement('button');
        deleteButton.textContent = 'Delete';
        deleteButton.addEventListener('click', () => this.deleteTask(task.id));
        actions.appendChild(deleteButton);

        taskElement.appendChild(actions);

        return taskElement;
    }

    toggleTaskCompletion(id) {
        const task = this.taskManager.toggleTaskCompletion(id);
        if (task) {
            this.renderTasks();
        }
    }

    editTask(id) {
        const task = this.taskManager.getTask(id);
        if (task) {
            this.titleInput.value = task.title;
            this.descriptionInput.value = task.description;
            this.dueDateInput.value = task.dueDate;
            this.priorityInput.value = task.priority;
            this.submitButton.textContent = 'Update Task';
            this.editingTask = task;
        }
    }

    deleteTask(id) {
        const success = this.taskManager.removeTask(id);
        if (success) {
            this.renderTasks();
        }
    }

    handleSubmit(event) {
        event.preventDefault();

        const title = this.titleInput.value.trim();
        const description = this.descriptionInput.value.trim();
        const dueDate = this.dueDateInput.value.trim();
        const priority = this.priorityInput.value.trim();

        if (!title || !description || !dueDate || !priority) {
            alert('All fields are required.');
            return;
        }

        if (this.editingTask) {
            this.taskManager.updateTask(this.editingTask.id, title, description, dueDate, priority);
            this.editingTask = null;
            this.submitButton.textContent = 'Add Task';
        } else {
            this.taskManager.addTask(title, description, dueDate, priority);
        }

        this.clearForm();
        this.renderTasks();
    }

    clearForm() {
        this.titleInput.value = '';
        this.descriptionInput.value = '';
        this.dueDateInput.value = '';
        this.priorityInput.value = '';
    }
}

// Initialize TaskManager and TaskUI
const taskManager = new TaskManager();
const taskUI = new TaskUI(taskManager);

