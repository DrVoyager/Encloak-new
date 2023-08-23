import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import soot.Body;
import soot.G;
import soot.Local;
import soot.Modifier;
import soot.PatchingChain;
import soot.RefType;
import soot.SootField;
import soot.Unit;
import soot.Value;
import soot.ValueBox;
import soot.jimple.AssignStmt;
import soot.jimple.Constant;
import soot.jimple.FieldRef;
import soot.jimple.IdentityStmt;
import soot.jimple.IfStmt;
import soot.jimple.InstanceFieldRef;
import soot.jimple.Jimple;
import soot.util.Chain;


public class SetTaintSources {
	public SetTaintSources(
			Body body,
			List<Value> list,
			String taintSourceName) {
		// TODO Auto-generated constructor stub
		
			List<Value> newlist = new ArrayList<>();
			
//			Chain<SootField> fields= body.getMethod().getDeclaringClass().getFields();
//			for (SootField field : fields) {
//			    String fieldName = field.getName();
//			    G.v().out.println("fieldName: " + fieldName);
//			    
//			    if (Modifier.isStatic(field.getModifiers())) {
//			        // 如果字段是静态字段，则使用 newStaticFieldRef()方法获取其值
//			    	G.v().out.println("===static field===");
//			        FieldRef fieldRef = Jimple.v().newStaticFieldRef(field.makeRef());
//			        Value fieldValue = fieldRef;
//			        G.v().out.println("fieldValue: " + fieldValue);
//			        if(!newlist.contains(fieldValue)&& fieldValue.toString().equals(taintSourceName)){
//			        	G.v().out.println("added");
//			        	newlist.add(fieldValue);
//			        }
//			        
//			    } else {
//			        // 如果字段是实例字段，则需要先创建一个对象实例，并使用 newInstanceFieldRef() 方法获取其值
//			    	G.v().out.println("===instance field===");
//			        Local obj = Jimple.v().newLocal("obj", RefType.v(field.getDeclaringClass().getName()));
//			        InstanceFieldRef fieldRef = Jimple.v().newInstanceFieldRef(obj, field.makeRef());
//			        Value fieldValue = fieldRef;
//			        G.v().out.println("fieldValue: " + fieldValue);
//			        if(!newlist.contains(fieldValue)&& fieldValue.toString().equals(taintSourceName)){
//			        	G.v().out.println("added");
//			        	newlist.add(fieldValue);
//			        }
//			    }
//			}
			
			
			Unit currStmt = null;
			PatchingChain<Unit> units = body.getUnits();//all statements
			Iterator<Unit> scanIt1 = units.snapshotIterator();
			
			while (scanIt1.hasNext()) {
	
	    		currStmt = scanIt1.next();
	    		G.v().out.println("unit20210710 :"+currStmt.toString());
	    		if(currStmt instanceof IfStmt){
	    			//IfStmt
	    			G.v().out.println("If statment");
	    			
	    			Value orgIfCondition = ((IfStmt) currStmt).getCondition();
	    			//orgIfCondition.getUseBoxes().
	    			Iterator<ValueBox> ubIt=orgIfCondition.getUseBoxes().iterator();
	    			    			
	    			while(ubIt.hasNext()){
	    				ValueBox vBox = (ValueBox) ubIt.next();
	    				Value tValue = vBox.getValue();
	    				G.v().out.println("the value="+tValue);
	    				if (tValue instanceof Constant) {
							continue;
						}
	    				if(!newlist.contains(tValue)&& tValue.toString().equals(taintSourceName)) {
	    					newlist.add(tValue);
	    					break;
						}
	    				
	    			}
	    		}
	    		else if(currStmt instanceof AssignStmt){
	    			G.v().out.println("AssignStmt statment");
	    			
	    			Iterator<ValueBox> ubIt=currStmt.getUseAndDefBoxes().iterator();
	    			// $r0[0] = 2, tValue includes $r0[0], $r0, 0, 2			
	    			while(ubIt.hasNext()){
	    				ValueBox vBox = (ValueBox) ubIt.next();
	    				Value tValue = vBox.getValue();
	    				G.v().out.println("the value="+tValue);
	    				
	    				if (tValue instanceof Constant) {
	    					G.v().out.println("i0 is constant");
							continue;
						}
	    				G.v().out.println("2021="+newlist.contains(tValue)+" taintSourceName="+taintSourceName);
	    				if(!newlist.contains(tValue)&& tValue.toString().equals(taintSourceName)) {
	    					newlist.add(tValue);
	    					G.v().out.println("the value of newlist="+newlist.toString());
	    					break;
						}
	    			}
	    		}
	    		else if(currStmt instanceof IdentityStmt){
	    			G.v().out.println("Identity statment");
	    			Iterator<ValueBox> ubIt=currStmt.getUseAndDefBoxes().iterator();
	    			    			
	    			while(ubIt.hasNext()){
	    				ValueBox vBox = (ValueBox) ubIt.next();
	    				Value tValue = vBox.getValue();
	    				G.v().out.println("the value="+tValue);
	    				if (tValue instanceof Constant) {
	    					G.v().out.println("tValue instanceof Constant");
							continue;
						}
	    				if(!newlist.contains(tValue)&& tValue.toString().equals(taintSourceName)) {
	    					newlist.add(tValue);
	    					G.v().out.println("tValue added in newList");
	    					break;
						}
	    			}
	    		}
	    		else {
	    			G.v().out.println("other type currStmt");
	    		}
		}
		list.addAll(newlist);
	}
}
