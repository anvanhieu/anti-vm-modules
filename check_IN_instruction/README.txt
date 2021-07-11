DETECTION USING IN INSTRUCTION
The VMware virtual machine has an I/O port communication
channel, through which it exchanges data between the host
OS and the guest OS. If analysts use the IN instruction,
they can obtain information about I/O port. Additionally,
if analysts execute the IN instruction by inserting the value
0x5658 (i.e.,VX) in the DX register (i.e., the communication
channel), the value containing the information of the virtual
machine is stored in the EAX or EBX register. Therefore, it is
possible to detect the virtual machine using the IN instruction.