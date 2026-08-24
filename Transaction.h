#pragma once

#include <string>
enum class TransactionType {
    INCOME,
    EXPENSE,
    SAVING
};

class Transaction {
private:
    int id;                
    int userId;               
    double amount;            
    TransactionType type;     
    std::string category;     
    std::string description; 
    std::string date;       

    // fields specific to SAVING transactions
    int savingId;            // optional identifier for a savings goal
    double targetAmount;     // target amount for the savings goal
    double savedAmount;      // amount currently saved toward the goal
  

public:
   
    Transaction();
    Transaction(int id, int userId, double amount, TransactionType type,std::string category, std::string description, std::string date,
                int savingId = 0, double targetAmount = 0.0, double savedAmount = 0.0);

  
    ~Transaction() = default;

 
    int getId() const;
    int getUserId() const;
    double getAmount() const;
    TransactionType getType() const;
    std::string getTypeAsString() const;
    std::string getCategory() const;
    std::string getDescription() const;
    std::string getDate() const;

    // saving-specific getters
    int getSavingId() const;
    double getTargetAmount() const;
    double getSavedAmount() const;
    

    void setAmount(double amount);
    void setType(TransactionType type);
    void setCategory(const std::string& category);
    void setDescription(const std::string& description);
    void setDate(const std::string& date);

    // saving-specific setters
    void setSavingId(int id);
    void setTargetAmount(double amt);
    void setSavedAmount(double amt);
   


};