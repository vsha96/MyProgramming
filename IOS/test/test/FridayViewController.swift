//
//  FridayViewController.swift
//  test
//
//  Created by Shulyugin on 12.12.16.
//  Copyright © 2016 Shulyugin. All rights reserved.
//

import UIKit

class FridayViewController: UIViewController, UITableViewDelegate, UITableViewDataSource {
    var items: [String] = ["алгебра","алгебра","матан","матан","спецхимия","спецхимия","физика","физика"]
    var time = ["9:00-9:45","9:55-10:40","10:50-11:35","11:50-12:35","12:45-13:30","13:45-14:30","14:40-15:25","15:35-16:20"]
    
    @IBOutlet weak var TableFriday: UITableView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        TableFriday.delegate = self
        TableFriday.dataSource = self
        TableFriday.tableFooterView = UIView()
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return items.count
    }
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = TableFriday.dequeueReusableCell(withIdentifier: "CellFriday")! as! TableViewCellMonday
        cell.LabelNameFriday.text = items[indexPath.row]
        cell.LabelTimeFriday.text = time[indexPath.row]
        return cell
    }
}
