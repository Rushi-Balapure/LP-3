# Assignment 4

## Title

Write a program in solidity to create Student data. Use the following constructs:
- Structures
- Arrays
- Fallback

Deploy this as smart contract on Ethereum and Observe the transaction fee and Gas values.

## Steps

1. Go to [Remix IDE](https://remix.ethereum.org/).

    ![image](https://github.com/user-attachments/assets/473734af-7376-4c8a-b554-ef083c1e63ed)

2. In the "File Explorer" tab, click the + icon to create a new file. Name the file `StudentData.sol`.

3. Copy the following code into the file

    ```sol
    // SPDX-License-Identifier: MIT
    pragma solidity ^0.8.0;
    
    contract StudentData {
        // Define a structure to hold student details
        struct Student {
            string name;
            uint256 age;
            string class;
            uint256 rollNumber;
        }
    
        // An array to hold all students
        Student[] public students;
    
        // Event to log student data when added
        event StudentAdded(string name, uint256 rollNumber);
    
        // Event to log Ether received in the fallback function
        event FallbackCalled(address sender, uint256 amount, string message);
    
        // Function to add a new student
        function addStudent(string memory _name, uint256 _age, string memory _class, uint256 _rollNumber) public {
            Student memory newStudent = Student({
                name: _name,
                age: _age,
                class: _class,
                rollNumber: _rollNumber
            });
            
            students.push(newStudent);
    
            // Emit an event to log the new student addition
            emit StudentAdded(_name, _rollNumber);
        }
    
        // Function to retrieve the total number of students
        function getTotalStudents() public view returns (uint256) {
            return students.length;
        }
    
        // Function to retrieve a student's details by index
        function getStudent(uint256 index) public view returns (string memory, uint256, string memory, uint256) {
            require(index < students.length, "Invalid index");
            Student memory student = students[index];
            return (student.name, student.age, student.class, student.rollNumber);
        }
    
        // Fallback function to handle unexpected calls or when there is data but no matching function
        fallback() external payable {
            // Emit an event to log the Ether received and a thank-you message
            emit FallbackCalled(msg.sender, msg.value, "Thank you for sending Ether!");
        }
    
        // Receive function to handle plain Ether transfers with no data
        receive() external payable {
            // Any Ether sent without data will be accepted here
        }
    
        // Function to check the balance of Ether in the contract
        function getContractBalance() public view returns (uint256) {
            return address(this).balance;
        }
    }

    ```

4. In the left sidebar, click on the Solidity Compiler (the "Compile" tab). Ensure the compiler version is set to `0.8.0` or higher (since we're using `^0.8.0` in the contract).
   
    Click the Compile Bank.sol button. If there are no errors, the contract will compile successfully.

5. Deploy the contract

    ![image](https://github.com/user-attachments/assets/0eaeeac9-a11f-4d59-afd3-9148b1d601a5)

6. Interact with the contract

    ![image](https://github.com/user-attachments/assets/9f1190f0-0a17-4f05-a140-efc1df6d9b9b)

### Testing the Fallback and Observing Gas Fees:

1. Sending Ether:

    You can send a small amount of Ether to the contract address using MetaMask. This will trigger the fallback function, and the Ether will be stored in the contract.
    Manually send Ether to the contract by copying the contract address from Remix and sending a transaction through MetaMask (this will trigger the fallback function).

    ![image](https://github.com/user-attachments/assets/70888cc6-2dc6-4cac-96a4-6c20df35e094)

    Send ETH from Metamask

    ![image](https://github.com/user-attachments/assets/913fe4c2-2eae-4ae7-b8ae-8f73ca8d5589)

    Enter the copied address here to send ETH
   
    ![image](https://github.com/user-attachments/assets/2365efdb-4b90-44f6-aea7-0ee2f1ac73cb)

    Enter the amount you want to send (I'm sending a very small amount of ETH)

    ![image](https://github.com/user-attachments/assets/b3db7e5d-ac30-4778-8122-57aa4fd50202)

    Hit Confirm

    ![image](https://github.com/user-attachments/assets/564723d3-ce3b-4188-873f-5e9dbddc6caa)

    After the given time has elapsed, the transaction will get completed.

    ![image](https://github.com/user-attachments/assets/96946f9d-10c6-4785-afbe-d409d81a917b)

    

3. Check Contract Balance:

    Use the getContractBalance function to verify that the Ether has been successfully transferred to the contract.

3. Observe Gas Fees:

    - After each transaction (adding a student, sending Ether, etc.), you can observe the Gas Fees and Gas Usage in MetaMask.
    - MetaMask provides a breakdown of the gas fees (in gwei) and the total cost in Ether for each transaction. Gas fees vary based on the network conditions and the complexity of the transaction.
    - Adding a Student involves writing to the blockchain and will incur a higher gas fee compared to reading functions like getStudent or getContractBalance.
