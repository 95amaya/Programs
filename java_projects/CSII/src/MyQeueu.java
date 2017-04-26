
public class MyQeueu {
	private MyLinkedList q;
	
	MyQeueu(){
		q = new MyLinkedList();
	}
	
	public void addLast(String e){ //Add newNode to end of LinkedList
		Node newNode = new Node(e);
		
		if(q.isEmpty())	
			q.addFirst(e);
		else{ //Traverse List until you get to the end then add newNode
			Node temp = q.first;
			
			while(temp.getNext() != null)
				temp = temp.getNext();
		
			temp.next = newNode;
		}
	}
	
	public void removeFirst(){ //Have first traverse to the next node
		if(q.isEmpty())
			System.out.println("Qeueu is Empty");
		else
			q.first = q.first.next;
	}
	
	public void printList(){//Use MyLinkedList method
		q.printList();
	}
	
	public boolean isEmpty(){//Use MyLinkedList method
		return q.isEmpty();
	}
	
	public int size(){ // Get size of Qeueu
		return q.size();
	}

}
