#include <iostream>
#include <string>

// Target Interface
class EmailService {
public:
    virtual void sendEmail(const std::string& to, const std::string& message) = 0;
    virtual ~EmailService() = default;
};

// Adaptee (Third-party library)
class SendGridAPI {
public:
    void send(const std::string& recipient, const std::string& subject, const std::string& body) {
        std::cout << "SendGrid: Email sent to " << recipient << " with subject '" << subject << "'\n";
    }
};

// Adapter
class SendGridAdapter : public EmailService {
    SendGridAPI sendGrid;
public:
    void sendEmail(const std::string& to, const std::string& message) override {
        std::string subject = "Notification";  // default subject
        sendGrid.send(to, subject, message);
    }
};

// Client
class NotificationSystem {
    EmailService& emailService;
public:
    NotificationSystem(EmailService& service) : emailService(service) {}
    void notifyUser(const std::string& userEmail) {
        emailService.sendEmail(userEmail, "Your report is ready!");
    }
};

// Demo
int main() {
    SendGridAdapter adapter;
    NotificationSystem notifier(adapter);
    notifier.notifyUser("user@example.com");
    return 0;
}