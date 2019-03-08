//
//  TimetableViewController.swift
//  prototype
//
//  Created by Shulyugin on 07.12.16.
//  Copyright © 2016 Shulyugin. All rights reserved.
//

import UIKit
import CoreData

class TimetableViewController: UIViewController, UITableViewDelegate, UITableViewDataSource {
    var items: [String] = [NSManagedObject]()
    var time = ["9-10","10-11","11-12","12-13","13-14","14-15","15-16","16-17","17-18"]
    
    @IBOutlet weak var TimetableItems: UITableView!
    override func viewDidLoad() {
        super.viewDidLoad()
        
        TimetableItems.delegate = self
        TimetableItems.dataSource = self
        
        // TimetableItems.separatorStyle = .none
        
        //hack
        TimetableItems.tableFooterView = UIView()
        
        
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return items.count
    }
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = TimetableItems.dequeueReusableCell(withIdentifier: "TimetableItemCell")! as! TimetableViewCell
        cell.LabelName.text = items[indexPath.row]
        cell.LabelTime.text = time[indexPath.row]
        return cell
    }
    
    func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath) {
        //var item = items1[indexPath.row] // берет значение названия для editor
        self.performSegue(withIdentifier: "TimetableToEditor", sender: nil)
    }
    
    
}

