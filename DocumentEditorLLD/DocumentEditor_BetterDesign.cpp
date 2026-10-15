#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<stack>
#include<stdexcept>

using namespace std;

// USER

class User {
    private:
      int id;
      string name;
      string email;
    public:
      User(int id,const string& name,const string& email):id(id),name(name),email(email){}

      int getId() const {return id;}

      string getName() const {return name;}

      string getEmail() const {return email;}
};

// Permission

enum class Permission{
    VIEWER,
    COMMENTER,
    EDITOR,
    OWNER
};

string permissionToString(Permission permission){
    switch(permission){
        case Permission::VIEWER: return "VIEWER";
        case Permission::COMMENTER: return "COMMENTER";
        case Permission::EDITOR: return "EDITOR";
        case Permission::OWNER: return "OWNER";
    }
    return "UNKNOWN";
}

// Collaborator

class Collaborator{
    private:
     shared_ptr<User> user;
     Permission permission;
    public:
     Collaborator(shared_ptr<User> user, Permission permission)
         : user(user), permission(permission) {}

     shared_ptr<User> getUser() const 
     {
        return user;
     }
     Permission getPermission() const {return permission;}

     void setPermission(Permission permission){
        this->permission = permission;
     }

     void display() const {
        cout << user->getName() << "->" << permissionToString(permission) << endl;
     }
    };

// TextStyle 

class TextStyle {
    private:
     bool bold;
     bool italic;
     bool underline;
     int fontSize;
    public:
     TextStyle(bool bold = false,bool italic = false,bool underline = false,int fontSize = 12):bold(bold),italic(italic),underline(underline),fontSize(fontSize){}

     bool isBold() const {return bold;}
     bool isItalic() const {return italic;}
     bool isUnderline() const {return underline;}
     int getFontSize() const {return fontSize;}
     void setBold(bool bold){this->bold = bold;}
     void setItalic(bool italic){this->italic = italic;}
     void setUnderline(bool underline){this->underline = underline;}
     void setFontSize(int fontSize){this->fontSize = fontSize;}
     void display() const {
        cout << "TextStyle: ";
        if(bold) cout << "Bold ";
        if(italic) cout << "Italic ";
        if(underline) cout << "Underline ";
        cout << "Font Size: " << fontSize << endl;
    }
};



// Text Run 
class TextRun{
    private:
      string text;
      TextStyle style;
    public:
      TextRun(const string& text,const TextStyle& style):text(text),style(style){}
      string getText() const {return text;}
      void setText(const string& text){this->text = text;}
      TextStyle& getStyle() { return style; }
      const TextStyle& getStyle() const { return style; }

      void display() const{
        cout << "\"" << text << "\" with style: ";
        cout<<"[";
        if(style.isBold()) cout<<"Bold ";
        if(style.isItalic()) cout<<"Italic ";
        if(style.isUnderline()) cout<<"Underline ";
        cout<<"Font Size: "<<style.getFontSize()<<"]"<<endl;
      }

};

// Document Element

class DocumentElement{
    public:
      virtual void display() const = 0;
      virtual ~DocumentElement() = default;
};

// Paragraph
class Paragraph : public DocumentElement{
    private:
     vector<TextRun>runs;
    public:
     void addText(const string& text,const TextStyle& style=TextStyle()){
        runs.emplace_back(text,style);
     }

     void removeRun(int index){
        if (index < 0 || index >= static_cast<int>(runs.size())) {
            throw out_of_range("Invalid index");
        }
        runs.erase(runs.begin()+index);
     }

     // get run
     TextRun& getRun(int index) {
        if (index < 0 || index >= static_cast<int>(runs.size())) {
            throw out_of_range("Invalid run index");
        }

        return runs[index];
    }

    const TextRun& getRun(int index) const {
        if (index < 0 || index >= static_cast<int>(runs.size())) {
            throw out_of_range("Invalid run index");
        }

        return runs[index];
    }

    int getRunCount() const {
        return static_cast<int>(runs.size());
    }

    // Insert a run at a particular index
    void insertRun(
        int index,
        const TextRun& run
    ) {
        if (index < 0 || index > static_cast<int>(runs.size())) {
            throw out_of_range("Invalid insertion index");
        }

        runs.insert(runs.begin() + index, run);
    }

    void display() const override {
        cout << "Paragraph:\n";

        for (const auto& run : runs) {
            run.display();
        }

        cout << '\n';
    }


};

class Image : public DocumentElement {
    private:
        string url;
        int width;
        int height;
    
    public:
        Image(
            const string& url,
            int width,
            int height
        )
            : url(url),
              width(width),
              height(height) {}
    
        void display() const override {
            cout << "Image: "
                 << url
                 << " (" << width
                 << "x" << height
                 << ")\n";
        }
    };
    
    
    // ============================================================
    // 9. TABLE
    // ============================================================
    
    class Table : public DocumentElement {
    private:
        vector<vector<string>> cells;
    
    public:
        Table(int rows, int columns)
            : cells(rows, vector<string>(columns)) {}
    
        void setCell(
            int row,
            int column,
            const string& value
        ) {
            if (row < 0 ||
                row >= static_cast<int>(cells.size()) ||
                column < 0 ||
                column >= static_cast<int>(cells[row].size())) {
    
                throw out_of_range("Invalid table cell");
            }
    
            cells[row][column] = value;
        }
    
        void display() const override {
            cout << "Table:\n";
    
            for (const auto& row : cells) {
    
                for (const auto& cell : row) {
                    cout << "| " << cell << " ";
                }
    
                cout << "|\n";
            }
    
            cout << '\n';
        }
    };
    
    
    // ============================================================
    // 10. TEXT RANGE
    // ============================================================
    
    class TextRange {
    private:
        int start;
        int end;
    
    public:
        TextRange(int start, int end)
            : start(start), end(end) {}
    
        int getStart() const {
            return start;
        }
    
        int getEnd() const {
            return end;
        }
    };
    
    
    // ============================================================
    // 11. COMMENT
    // ============================================================
    
    class Comment {
    private:
        int id;
    
        shared_ptr<User> author;
    
        string text;
    
        TextRange range;
    
    public:
        Comment(
            int id,
            shared_ptr<User> author,
            const string& text,
            TextRange range
        )
            : id(id),
              author(author),
              text(text),
              range(range) {}
    
        void display() const {
            cout << "Comment #" << id
                 << " by "
                 << author->getName()
                 << ": "
                 << text
                 << " [Range: "
                 << range.getStart()
                 << "-"
                 << range.getEnd()
                 << "]\n";
        }
    };
    
    
    // ============================================================
    // 12. COMMAND INTERFACE
    // ============================================================
    
    class Command {
    public:
    
        virtual void execute() = 0;
    
        virtual void undo() = 0;
    
        virtual ~Command() = default;
    };
    
    
    // ============================================================
    // 13. INSERT TEXT COMMAND
    // ============================================================
    
    class InsertTextCommand : public Command {
    private:
        shared_ptr<Paragraph> paragraph;
    
        string text;
    
        TextStyle style;
    
        bool executed = false;
    
    public:
        InsertTextCommand(
            shared_ptr<Paragraph> paragraph,
            const string& text,
            const TextStyle& style
        )
            : paragraph(paragraph),
              text(text),
              style(style) {}
    
        void execute() override {
    
            if (!executed) {
                paragraph->addText(text, style);
    
                executed = true;
            }
        }
    
        void undo() override {
    
            if (executed) {
                paragraph->removeRun(
                    paragraph->getRunCount() - 1
                );
    
                executed = false;
            }
        }
    };
    
    
    // ============================================================
    // 14. DELETE TEXT COMMAND
    // ============================================================
    
    class DeleteTextCommand : public Command {
    private:
        shared_ptr<Paragraph> paragraph;
    
        int index;
    
        TextRun deletedRun;
    
        bool executed = false;
    
    public:
    
        DeleteTextCommand(
            shared_ptr<Paragraph> paragraph,
            int index
        )
            : paragraph(paragraph),
              index(index),
              deletedRun("", TextStyle()) {}
    
        void execute() override {
    
            if (!executed) {
    
                deletedRun =
                    paragraph->getRun(index);
    
                paragraph->removeRun(index);
    
                executed = true;
            }
        }
    
        void undo() override {
    
            if (executed) {
    
                paragraph->insertRun(
                    index,
                    deletedRun
                );
    
                executed = false;
            }
        }
    };
    
    
    // ============================================================
    // 15. FORMAT TEXT COMMAND
    // ============================================================
    
    class FormatTextCommand : public Command {
    private:
        shared_ptr<Paragraph> paragraph;
    
        int index;
    
        TextStyle newStyle;
    
        TextStyle oldStyle;
    
        bool executed = false;
    
    public:
    
        FormatTextCommand(
            shared_ptr<Paragraph> paragraph,
            int index,
            const TextStyle& newStyle
        )
            : paragraph(paragraph),
              index(index),
              newStyle(newStyle),
              oldStyle() {}
    
        void execute() override {
    
            if (!executed) {
    
                oldStyle =
                    paragraph->getRun(index).getStyle();
    
                paragraph
                    ->getRun(index)
                    .getStyle() = newStyle;
    
                executed = true;
            }
        }
    
        void undo() override {
    
            if (executed) {
    
                paragraph
                    ->getRun(index)
                    .getStyle() = oldStyle;
    
                executed = false;
            }
        }
    };
    
    
    // ============================================================
    // 16. VERSION
    // ============================================================
    
    class Version {
    private:
        int versionId;
    
        string description;
    
    public:
    
        Version(
            int versionId,
            const string& description
        )
            : versionId(versionId),
              description(description) {}
    
        void display() const {
            cout << "Version "
                 << versionId
                 << ": "
                 << description
                 << '\n';
        }
    };
    
    
    // ============================================================
    // 17. VERSION HISTORY
    // ============================================================
    
    class VersionHistory {
    private:
        vector<Version> versions;
    
    public:
    
        void createVersion(
            const string& description
        ) {
    
            int id =
                static_cast<int>(versions.size()) + 1;
    
            versions.emplace_back(
                id,
                description
            );
        }
    
        void showHistory() const {
    
            cout << "\n===== VERSION HISTORY =====\n";
    
            for (const auto& version : versions) {
                version.display();
            }
    
            cout << "============================\n";
        }
    };
    
    
    // ============================================================
    // 18. DOCUMENT
    // ============================================================
    
    class Document {
    private:
    
        int id;
    
        string title;
    
        // Different elements of document
        vector<shared_ptr<DocumentElement>> elements;
    
        // Users having access to document
        vector<Collaborator> collaborators;
    
        // Comments
        vector<Comment> comments;
    
        // Undo / Redo
        stack<shared_ptr<Command>> undoStack;
    
        stack<shared_ptr<Command>> redoStack;
    
    public:
    
        Document(
            int id,
            const string& title
        )
            : id(id),
              title(title) {}
    
        // --------------------------------------------------------
        // ELEMENT MANAGEMENT
        // --------------------------------------------------------
    
        void addElement(
            shared_ptr<DocumentElement> element
        ) {
            elements.push_back(element);
        }
    
        // --------------------------------------------------------
        // COLLABORATOR MANAGEMENT
        // --------------------------------------------------------
    
        void addCollaborator(
            const Collaborator& collaborator
        ) {
            collaborators.push_back(collaborator);
        }
    
        // --------------------------------------------------------
        // COMMENT MANAGEMENT
        // --------------------------------------------------------
    
        void addComment(
            const Comment& comment
        ) {
            comments.push_back(comment);
        }
    
        // --------------------------------------------------------
        // COMMAND EXECUTION
        // --------------------------------------------------------
    
        void executeCommand(
            shared_ptr<Command> command
        ) {
    
            command->execute();
    
            undoStack.push(command);
    
            // New operation means old redo history is invalid
            while (!redoStack.empty()) {
                redoStack.pop();
            }
        }
    
        // --------------------------------------------------------
        // UNDO
        // --------------------------------------------------------
    
        void undo() {
    
            if (undoStack.empty()) {
                cout << "Nothing to undo.\n";
                return;
            }
    
            auto command =
                undoStack.top();
    
            undoStack.pop();
    
            command->undo();
    
            redoStack.push(command);
        }
    
        // --------------------------------------------------------
        // REDO
        // --------------------------------------------------------
    
        void redo() {
    
            if (redoStack.empty()) {
                cout << "Nothing to redo.\n";
                return;
            }
    
            auto command =
                redoStack.top();
    
            redoStack.pop();
    
            command->execute();
    
            undoStack.push(command);
        }
    
        // --------------------------------------------------------
        // DISPLAY DOCUMENT
        // --------------------------------------------------------
    
        void display() const {
    
            cout << "\n";
            cout << "====================================\n";
            cout << "Document: " << title << '\n';
            cout << "====================================\n";
    
            for (const auto& element : elements) {
                element->display();
            }
        }
    
        // --------------------------------------------------------
        // DISPLAY COLLABORATORS
        // --------------------------------------------------------
    
        void displayCollaborators() const {
    
            cout << "\n===== COLLABORATORS =====\n";
    
            for (const auto& collaborator : collaborators) {
                collaborator.display();
            }
        }
    
        // --------------------------------------------------------
        // DISPLAY COMMENTS
        // --------------------------------------------------------
    
        void displayComments() const {
    
            cout << "\n===== COMMENTS =====\n";
    
            for (const auto& comment : comments) {
                comment.display();
            }
        }
    };
    
    
    // ============================================================
    // 19. MAIN
    // ============================================================
    
    int main() {
    
        // --------------------------------------------------------
        // USERS
        // --------------------------------------------------------
    
        auto satyapal =
            make_shared<User>(
                1,
                "Satyapal",
                "satyapal@gmail.com"
            );
    
        auto rahul =
            make_shared<User>(
                2,
                "Rahul",
                "rahul@gmail.com"
            );
    
        auto aman =
            make_shared<User>(
                3,
                "Aman",
                "aman@gmail.com"
            );
    
    
        // --------------------------------------------------------
        // CREATE DOCUMENT
        // --------------------------------------------------------
    
        Document document(
            101,
            "My Google Docs"
        );
    
    
        // --------------------------------------------------------
        // CREATE PARAGRAPH
        // --------------------------------------------------------
    
        auto paragraph =
            make_shared<Paragraph>();
    
    
        // Normal style
    
        TextStyle normalStyle;
    
    
        // Bold style
    
        TextStyle boldStyle;
    
        boldStyle.setBold(true);
    
    
        // Italic style
    
        TextStyle italicStyle;
    
        italicStyle.setItalic(true);
    
    
        // --------------------------------------------------------
        // ADD PARAGRAPH TO DOCUMENT
        // --------------------------------------------------------
    
        document.addElement(paragraph);
    
    
        // --------------------------------------------------------
        // INSERT TEXT USING COMMAND
        // --------------------------------------------------------
    
        auto command1 =
            make_shared<InsertTextCommand>(
                paragraph,
                "Hello ",
                normalStyle
            );
    
        document.executeCommand(command1);
    
    
        auto command2 =
            make_shared<InsertTextCommand>(
                paragraph,
                "Google",
                boldStyle
            );
    
        document.executeCommand(command2);
    
    
        auto command3 =
            make_shared<InsertTextCommand>(
                paragraph,
                " Docs",
                italicStyle
            );
    
        document.executeCommand(command3);
    
    
        // --------------------------------------------------------
        // ADD IMAGE
        // --------------------------------------------------------
    
        auto image =
            make_shared<Image>(
                "profile.jpg",
                400,
                300
            );
    
        document.addElement(image);
    
    
        // --------------------------------------------------------
        // ADD TABLE
        // --------------------------------------------------------
    
        auto table =
            make_shared<Table>(3, 2);
    
        table->setCell(0, 0, "Name");
        table->setCell(0, 1, "Marks");
    
        table->setCell(1, 0, "Rahul");
        table->setCell(1, 1, "90");
    
        table->setCell(2, 0, "Aman");
        table->setCell(2, 1, "85");
    
        document.addElement(table);
    
    
        // --------------------------------------------------------
        // DISPLAY DOCUMENT
        // --------------------------------------------------------
    
        document.display();
    
    
        // --------------------------------------------------------
        // COLLABORATORS
        // --------------------------------------------------------
    
        document.addCollaborator(
            Collaborator(
                satyapal,
                Permission::OWNER
            )
        );
    
        document.addCollaborator(
            Collaborator(
                rahul,
                Permission::EDITOR
            )
        );
    
        document.addCollaborator(
            Collaborator(
                aman,
                Permission::VIEWER
            )
        );
    
        document.displayCollaborators();
    
    
        // --------------------------------------------------------
        // COMMENT
        // --------------------------------------------------------
    
        Comment comment(
            1,
            rahul,
            "Please review this section.",
            TextRange(6, 12)
        );
    
        document.addComment(comment);
    
        document.displayComments();
    
    
        // --------------------------------------------------------
        // UNDO
        // --------------------------------------------------------
    
        cout << "\n\n===== UNDO =====\n";
    
        document.undo();
    
        document.display();
    
    
        // --------------------------------------------------------
        // REDO
        // --------------------------------------------------------
    
        cout << "\n\n===== REDO =====\n";
    
        document.redo();
    
        document.display();
    
    
        // --------------------------------------------------------
        // VERSION HISTORY
        // --------------------------------------------------------
    
        VersionHistory history;
    
        history.createVersion(
            "Initial document created"
        );
    
        history.createVersion(
            "Added text"
        );
    
        history.createVersion(
            "Added image and table"
        );
    
        history.showHistory();
    
    
        return 0;
    }